#include <string>
#include <iostream>
#include <filesystem>
#include "../error/error.hpp"
#include "lexer/st_lexer.hpp"
#include "file/file_utils.hpp"
#include "console/command_line_parser.hpp"
#include "parser/st_parser.hpp"

#include <llvm/Target/TargetMachine.h>
#include <llvm/Target/TargetOptions.h>
#include <llvm/TargetParser/Host.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/MC/TargetRegistry.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/IR/DataLayout.h>

enum class CommandLineFlags : unsigned int
{
    HELP,
    OUTPUT_FILE,
    VERBOSE,
    OUTPUT_C_HEADER,
    TARGET_TRIPLE,
    EMIT_LL_WITH_ERRORS,
    ENTRY_POINT,
};

void RegisterCommands(CommandLineParser<CommandLineFlags> *command_line)
{
    command_line->RegisterFlag(CommandLineFlags::HELP, 0, {"-h", "--help"});
    command_line->RegisterFlag(CommandLineFlags::OUTPUT_FILE, 1, {"-o"});
    command_line->RegisterFlag(CommandLineFlags::VERBOSE, 0, {"-v", "--verbose"});
    command_line->RegisterFlag(CommandLineFlags::OUTPUT_C_HEADER, 1, {"--output-c-header"});
    command_line->RegisterFlag(CommandLineFlags::TARGET_TRIPLE, 1, {"-target"});
    command_line->RegisterFlag(CommandLineFlags::EMIT_LL_WITH_ERRORS, 0, {"--emit_ll_with_errors"});
    command_line->RegisterFlag(CommandLineFlags::ENTRY_POINT, 1, {"--entry_point"});
}

CommandLineParser<CommandLineFlags> ParseCommandLine(int argc, char const *argv[])
{
    CommandLineParser<CommandLineFlags> command_line;
    RegisterCommands(&command_line);
    command_line.Parse(argc, argv);
    return command_line;
}

llvm::Constant *LLVMSizeof(AST::LLVMCompilerContext *llvm_cc, llvm::Type *type)
{
    llvm::TypeSize size = llvm_cc->module->getDataLayout().getTypeAllocSize(type);
    uint64_t size_int = size.getFixedValue();

    llvm::Type *int_type = llvm::IntegerType::getInt32Ty(*llvm_cc->context);
    llvm::Constant *const_val = llvm::ConstantInt::get(int_type, llvm::APInt(32, size_int, false));

    return const_val;
}

void CreateProgramDescription(AST::LLVMCompilerContext *llvm_cc, AST::Program *entry_program)
{
    // setup pointer to main program (structure containing pointer to main and other usefull data)
    assert(entry_program);

    llvm::Function *program = entry_program->LLVMGetBodyDeclaration(llvm_cc);
    llvm::Function *program_init = entry_program->LLVMGetInitDeclaration(llvm_cc);
    llvm::StructType *program_struct = entry_program->LLVMGetStructType(llvm_cc);

    assert(program != nullptr && program_init != nullptr && program_struct != nullptr);

    std::vector<llvm::Type *> struct_element_types =
        {program->getType(),
         program_init->getType(),
         llvm::Type::getInt32Ty(*llvm_cc->context)};

    llvm::StructType *struct_type = llvm::StructType::get(
        *llvm_cc->context,
        struct_element_types,
        true);

    // initializer

    std::vector<llvm::Constant *> struct_element_values =
        {program,
         program_init,
         LLVMSizeof(llvm_cc, program_struct)};

    llvm::Constant *struct_value = llvm::ConstantStruct::get(struct_type, struct_element_values);

    llvm::GlobalVariable *GV = new llvm::GlobalVariable(
        *llvm_cc->module,
        struct_type,
        true,
        llvm::GlobalValue::LinkageTypes::ExternalLinkage,
        struct_value,
        "@ModuleDescription");

    GV->setSection("main.symbol_table");
}

// This function might be removed
// void EmitExecutable()
// {
//     auto Filename = "output.o";
//     std::error_code EC;

//     std::string output;
//     llvm::raw_fd_ostream dest(Filename, EC, llvm::sys::fs::OF_None);

//     llvm::legacy::PassManager pass;
//     auto FileType = llvm::CodeGenFileType::ObjectFile;
//     // auto FileType = llvm::CodeGenFileType::AssemblyFile;

//     if (TargetMachine->addPassesToEmitFile(pass, dest, nullptr, FileType))
//     {
//         llvm::errs() << "TargetMachine can't emit a file of this type";
//         return 1;
//     }

//     {
//         for (auto &t_ptr : llvm::TargetRegistry::targets())
//         {
//             std::cout << "TARGET: " << t_ptr.getShortDescription() << "\n";
//         }
//     }

//     pass.run(*llvm_cc.module);
//     dest.flush();
// }

static void VerifyModule(llvm::Module *module)
{
    std::string code_err;
    llvm::raw_string_ostream ostream(code_err);
    llvm::verifyModule(*module, &ostream);

    if (code_err.size())
    {
        ErrorManager::Create(Error::InternalCompilerError(code_err));
    }
}

AST::PouPtr FindPouWithNameWithName(std::string name, const AST::PouList &pou_list)
{
    for (AST::PouPtr pou : pou_list)
    {
        if (pou)
        {
            if (pou->name == name)
            {
                return pou;
            }
        }
    }

    return nullptr;
}

int main(int argc, char const *argv[])
{
    CommandLineParser<CommandLineFlags> command_line = ParseCommandLine(argc, argv);

    bool IsVerbose = false;
    if (command_line.IsFlagUsed(CommandLineFlags::VERBOSE))
    {
        IsVerbose = true;
    }

    // read files
    std::vector<std::string> input_file_paths = command_line.GetFiles();
    if (input_file_paths.size() == 0)
    {
        ErrorManager::Create(Error::NoInputFiles());
        // Error::PrintErrors();
        return -1;
    }

    std::vector<File> files = ReadFileList(command_line.GetFiles());

    LLVMInitializeARMTarget();
    LLVMInitializeARMTargetInfo();
    LLVMInitializeARMTargetMC();
    // LLVMInitializeARMAsmPrinter();
    // LLVMInitializeARMAsmParser();

    llvm::InitializeNativeTarget();
    // llvm::InitializeNativeTargetAsmParser();
    // llvm::InitializeNativeTargetAsmPrinter();

    std::string tt = llvm::sys::getDefaultTargetTriple(); // this will be default if not -target is provided
    if (command_line.IsFlagUsed(CommandLineFlags::TARGET_TRIPLE))
    {
        if (command_line.GetFlagArgs(CommandLineFlags::TARGET_TRIPLE).size() >= 1)
        {
            tt = command_line.GetFlagArgs(CommandLineFlags::TARGET_TRIPLE)[0];
        }
    }

    std::string Error;
    auto Target = llvm::TargetRegistry::lookupTarget(tt, Error);

    auto CPU = "";
    auto Features = "";

    llvm::TargetOptions opt;
    // opt.FloatABIType = llvm::FloatABI::ABIType::Soft;
    // opt.ThreadModel = llvm::ThreadModel::Single;
    // opt.ExceptionModel = llvm::ExceptionHandling::None;

    auto TargetMachine = Target->createTargetMachine(tt, CPU, Features, opt, llvm::Reloc::PIC_);
    auto dl = TargetMachine->createDataLayout();

    AST::LLVMCompilerContext llvm_cc;
    AST::PouList pou_list;

    llvm_cc.module->setTargetTriple(tt);
    llvm_cc.module->setDataLayout(dl);

    // std::vector<Lexer::TokenList> tokens_from_files = Lexer::TokenizeFiles(err, files);

    for (auto &file : files)
    {
        std::filesystem::path path = file.path;
        bool is_extern = path.extension() == ".st_extern";

        Lexer::TokenList tokens = Lexer::Tokenize(file.path, file.content);

        AST::PouList pous = StParser::Parse(tokens, is_extern);
        pou_list.insert(pou_list.end(), pous.begin(), pous.end());
    }

    // for (Lexer::TokenList t : tokens_from_files)
    // {
    //     AST::PouList pous = StParser::Parse(err, t);
    //     pou_list.insert(pou_list.end(), pous.begin(), pous.end());
    // }

    for (AST::PouPtr pou : pou_list)
    {
        pou->LLVMGenerateDeclaration(&pou_list, &llvm_cc);
    }

    for (AST::PouPtr pou : pou_list)
    {
        pou->LLVMGenerateDefinition(&pou_list, &llvm_cc);
    }

    // find entry point

    std::string entry_point_name = "main";
    
    if (command_line.IsFlagUsed(CommandLineFlags::ENTRY_POINT))
    {
        if (command_line.GetFlagArgs(CommandLineFlags::ENTRY_POINT).size() >= 1)
        {
            entry_point_name = command_line.GetFlagArgs(CommandLineFlags::ENTRY_POINT)[0];
        }
    }
    
    if (AST::PouPtr pou = FindPouWithNameWithName(entry_point_name, pou_list))
    {
        if (AST::Program *entry_prog = dynamic_cast<AST::Program *>(pou.get()))
        {
            CreateProgramDescription(&llvm_cc, entry_prog);
        }
        else
        {
            ErrorManager::Create(Error::EntryPointMustBeProgram(entry_point_name));
        }
    }
    else
    {
        ErrorManager::Create(Error::CannotFindEntryPoint(entry_point_name));
    }

    // Error::PrintErrors();

    // verify module
    VerifyModule(llvm_cc.module.get());

    if (ErrorManager::Count())
    {
        if (command_line.IsFlagUsed(CommandLineFlags::EMIT_LL_WITH_ERRORS))
        {
            std::cout << Console::FgBrightYellow("[WARNING]") + " Emiting llvm ir code regardless of errors (used --emit_ll_with_errors)\n";
        }
        else
        {
            return -1;
        }
    }

    File output_ir_file;
    output_ir_file.path = "output.ll";
    output_ir_file.content = llvm_cc.IR_ToString();

    if (command_line.IsFlagUsed(CommandLineFlags::OUTPUT_FILE))
    {
        if (command_line.GetFlagArgs(CommandLineFlags::OUTPUT_FILE).size() >= 1)
        {
            output_ir_file.path = command_line.GetFlagArgs(CommandLineFlags::OUTPUT_FILE)[0];
        }
    }

    if (IsVerbose)
    {
        std::cout << Console::BgDarkCyan("======================================\n");
        std::cout << "Saving IR code at: " << output_ir_file.path << "\n";
        std::cout << Console::BgDarkCyan("======================================\n");
        std::cout << output_ir_file.content << "\n";
        std::cout << Console::BgDarkCyan("======================================\n");
        std::cout << "Emiting IR for target: " << TargetMachine->getTargetTriple().str() << "\n";
    }

    WriteFile(&output_ir_file);

    // for (llvm::Function &func : llvm_cc.module->getFunctionList())
    // {
    //     // func.viewCFG();
    // }

    std::cout.flush();
    return 0;
}
