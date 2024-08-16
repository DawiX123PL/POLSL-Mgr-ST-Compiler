#include <string>
#include <iostream>
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
    TARGET_TRIPLE
};

void RegisterCommands(CommandLineParser<CommandLineFlags> *command_line)
{
    command_line->RegisterFlag(CommandLineFlags::HELP, 0, {"-h", "--help"});
    command_line->RegisterFlag(CommandLineFlags::OUTPUT_FILE, 1, {"-o"});
    command_line->RegisterFlag(CommandLineFlags::VERBOSE, 0, {"-v", "--verbose"});
    command_line->RegisterFlag(CommandLineFlags::OUTPUT_C_HEADER, 1, {"--output-c-header"});
    command_line->RegisterFlag(CommandLineFlags::TARGET_TRIPLE, 1, {"-target"});
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

void CreateProgramDescription(AST::LLVMCompilerContext *llvm_cc)
{
    // setup pointer to main program (structure containing pointer to main and other usefull data)

    std::string program_name = "main";
    llvm::Function *program = llvm_cc->module->getFunction(program_name);
    llvm::Function *program_init = llvm_cc->module->getFunction(program_name + ".init");
    llvm::StructType *program_struct = nullptr;
    {
        for (llvm::StructType *prog_struct : llvm_cc->module->getIdentifiedStructTypes())
        {
            if (prog_struct->hasName() && prog_struct->getName() == program_name + ".struct")
            {
                program_struct = prog_struct;
            }
        }
    }

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

int main(int argc, char const *argv[])
{
    Error::ErrorList_t err;

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
        Error::PushError(err, Error::NoInputFiles());
        Error::PrintErrors(err);
        return -1;
    }

    std::vector<File> files = ReadFileList(err, command_line.GetFiles());

    std::vector<Lexer::TokenList> tokens_from_files = Lexer::TokenizeFiles(err, files);

    LLVMInitializeARMTarget();
    LLVMInitializeARMTargetInfo();
    LLVMInitializeARMTargetMC();
    // LLVMInitializeARMAsmPrinter();
    // LLVMInitializeARMAsmParser();

    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmParser();
    llvm::InitializeNativeTargetAsmPrinter();

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

    for (Lexer::TokenList t : tokens_from_files)
    {
        AST::PouList pous = StParser::Parse(err, t);
        pou_list.insert(pou_list.end(), pous.begin(), pous.end());
    }

    for (AST::PouPtr pou : pou_list)
    {
        pou->LLVMGenerateDeclaration(&llvm_cc);
    }

    for (AST::PouPtr pou : pou_list)
    {
        pou->LLVMGenerateDefinition(&llvm_cc);
    }

    CreateProgramDescription(&llvm_cc);

    Error::PrintErrors(err);
    if (err.size())
    {
        return -1;
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

    WriteFile(err, &output_ir_file);

    // for (llvm::Function &func : llvm_cc.module->getFunctionList())
    // {
    //     // func.viewCFG();
    // }

    std::cout.flush();
    return 0;
}
