#include <string>
#include <iostream>
#include "error.hpp"
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

enum class CommandLineFlags : unsigned int
{
    HELP,
    OUTPUT_FILE,
    VERBOSE,
    OUTPUT_C_HEADER,
};

void RegisterCommands(CommandLineParser<CommandLineFlags> *command_line)
{
    command_line->RegisterFlag(CommandLineFlags::HELP, 0, {"-h", "--help"});
    command_line->RegisterFlag(CommandLineFlags::OUTPUT_FILE, 1, {"-o"});
    command_line->RegisterFlag(CommandLineFlags::VERBOSE, 0, {"-v", "--verbose"});
    command_line->RegisterFlag(CommandLineFlags::OUTPUT_C_HEADER, 1, {"--output-c-header"});
}

CommandLineParser<CommandLineFlags> ParseCommandLine(int argc, char const *argv[])
{
    CommandLineParser<CommandLineFlags> command_line;
    RegisterCommands(&command_line);
    command_line.Parse(argc, argv);
    return command_line;
}

int main(int argc, char const *argv[])
{
    Error::ErrorList_t err;

    CommandLineParser<CommandLineFlags> command_line = ParseCommandLine(argc, argv);

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

    AST::LLVMCompilerContext llvm_cc;
    AST::PouList pou_list;


    // llvm::InitializeAllTargetInfos();
    // llvm::InitializeAllTargets();
    // llvm::InitializeAllTargetMCs();
    // llvm::InitializeAllAsmParsers();
    // llvm::InitializeAllAsmPrinters();

    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmParser();
    llvm::InitializeNativeTargetAsmPrinter();

    auto tt = llvm::sys::getDefaultTargetTriple();

    std::string Error;
    auto Target = llvm::TargetRegistry::lookupTarget(tt, Error);

    auto CPU = "generic";
    auto Features = "";

    llvm::TargetOptions opt;
    auto TargetMachine = Target->createTargetMachine(tt, CPU, Features, opt, llvm::Reloc::PIC_);
    
    auto dl = TargetMachine->createDataLayout();

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

    std::cout << Console::BgDarkCyan("======================================\n");
    Error::PrintErrors(err);

    std::cout << Console::BgDarkCyan("======================================\n");
    std::cout << llvm_cc.IR_ToString();

    std::cout << Console::BgDarkCyan("======================================\n");
    auto TargetTriple = llvm::sys::getDefaultTargetTriple();
    std::cout << "Compiling for target: " << TargetTriple << "\n";

    for (llvm::Function &func : llvm_cc.module->getFunctionList())
    {
        // func.viewCFG();
    }

    auto Filename = "output.o";
    std::error_code EC;

    std::string output;
    llvm::raw_fd_ostream dest(Filename, EC, llvm::sys::fs::OF_None);

    llvm::legacy::PassManager pass;
    auto FileType = llvm::CodeGenFileType::ObjectFile;

    if (TargetMachine->addPassesToEmitFile(pass, dest, nullptr, FileType)) {
        llvm::errs() << "TargetMachine can't emit a file of this type";
        return 1;
    }

    pass.run(*llvm_cc.module);
    dest.flush();





    std::cout.flush();
    return 0;
}
