#include <string>
#include <iostream>
#include "error.hpp"
#include "lexer/st_lexer.hpp"
#include "file/file_utils.hpp"
#include "console/command_line_parser.hpp"
#include "parser/st_parser.hpp"


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

    // if (command_line.IsFlagUsed(CommandLineFlags::VERBOSE))
    // {
    //     PrintFileContent(file_content);
    // }

    std::vector<Lexer::TokenList> tokens_from_files = Lexer::TokenizeFiles(err, files);

    // if (command_line.IsFlagUsed(CommandLineFlags::VERBOSE))
    // {
    //     std::cout << Console::FgBrightBlue("[TOKEN COUNT]: ") << token_list.size() << "\n";
    //     for (int i = 0; i < token_list.size(); i++)
    //     {
    //         std::cout << Console::FgBrightBlue("[TOKEN]: ") << token_list[i].ToString() << "\n";
    //     }

    //     for (int i = 0; i < err.size(); i++)
    //     {
    //         std::cout << Console::FgBrightRed("[Error]: ") << err[i]->ToString() << "\n";
    //     }
    // }

    AST::LLVMCompilerContext llvm_cc;

    for (Lexer::TokenList t : tokens_from_files)
    {
        AST::PouList pou_list = StParser::Parse(err, t);
        for(AST::PouPtr pou: pou_list){
           std::cout<< pou->ToString() << "\n";
           pou->CodeGenLLVM(&llvm_cc);
        }
    }

    std::cout << Console::BgDarkCyan("======================================\n");
    Error::PrintErrors(err);

    std::cout << Console::BgDarkCyan("======================================\n");
    std::cout << llvm_cc.IR_ToString();

    std::cout.flush();

    // // AST::Function function;

    // err.clear();
    // AST::POUlist pou_list = Parse(err, token_list);

    // for (int i = 0; i < err.size(); i++)
    // {
    //     std::cout << Console::FgBrightRed("[Error]: ") << err[i]->ToString() << "\n";
    // }

    // AST::CompilerContext cc;
    // llvm::Function *fn = pou_list[0]->CodeGenLLVM(&cc);

    // if (command_line.IsFlagUsed(CommandLineFlags::VERBOSE))
    // {
    //     std::cout
    //         << Console::FgDarkGreen("[-------------------------------------------]: \n")
    //         << Console::FgDarkGreen("[Generated IR code]: \n")
    //         << cc.IR_ToString()
    //         << Console::FgDarkGreen("[End of Generated IR code]: \n")
    //         << Console::FgDarkGreen("[-------------------------------------------]: \n")
    //         << "\n";

    //     std::cout
    //         << Console::FgDarkGreen("[-------------------------------------------]: \n")
    //         << Console::FgDarkGreen("[Generated C/C++ header file]: \n")
    //         << pou_list[0]->CodeGenCHeader()
    //         << Console::FgDarkGreen("[End of Generated C/C++ header file]: \n")
    //         << Console::FgDarkGreen("[-------------------------------------------]: \n")
    //         << "\n";
    // }
    // // function.Evaluate();

    // if (!command_line.IsFlagUsed(CommandLineFlags::OUTPUT_FILE))
    // {
    //     std::cout << Console::FgBrightYellow("[Warning]: ") << "No output file specified\n";
    // }else{
    //     // output code to file
    //     std::string output_file_path = command_line.GetFlagArgs(CommandLineFlags::OUTPUT_FILE).front();
    //     std::string output_content = cc.IR_ToString();
    //     bool is_ok = WriteFileContent(output_file_path, output_content);
    // }

    // if (command_line.IsFlagUsed(CommandLineFlags::OUTPUT_C_HEADER))
    // {
    //     std::string c_header_file_path = command_line.GetFlagArgs(CommandLineFlags::OUTPUT_C_HEADER).front();
    //     std::string c_header_content = pou_list[0]->CodeGenCHeader();
    //     bool is_ok = WriteFileContent(c_header_file_path, c_header_content);
    // }

    // return 0;
}
