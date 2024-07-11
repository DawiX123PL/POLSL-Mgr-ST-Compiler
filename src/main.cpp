#include <string>
#include <iostream>
#include "lexer/st_lexer.hpp"
#include "file/file_utils.hpp"
#include "console/command_line_parser.hpp"
#include "parser/parser.hpp"


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


int main(int argc, char const *argv[])
{

    CommandLineParser<CommandLineFlags> command_line;
    RegisterCommands(&command_line);
    command_line.Parse(argc, argv);

    if (command_line.GetFiles().size() == 0)
    {
        std::cout << Console::FgBrightRed("[Error]: ") << "No input files\n";
        return -1;
    }

    if (command_line.GetFiles().size() != 1)
    {
        std::cout << Console::FgBrightYellow("[Warning]: ") << "More than one file provided. Ignoring extra files\n";
    }

    std::string input_file_name = command_line.GetFiles().front();

    std::string file_content;
    bool isok = ReadFileContent(input_file_name, &file_content);

    if (!isok)
    {
        std::cout << Console::FgBrightRed("[Error]: ") << "cannot read file: \"" + input_file_name << "\" \n";
        return -1;
    }

    if (command_line.IsFlagUsed(CommandLineFlags::VERBOSE))
    {
        PrintFileContent(file_content);
    }

    std::vector<Lexer::Token> token_list;
    ErrorList_t err;
    err = Lexer::Tokenize(file_content, &token_list);

    if (command_line.IsFlagUsed(CommandLineFlags::VERBOSE))
    {
        std::cout << Console::FgBrightBlue("[TOKEN COUNT]: ") << token_list.size() << "\n";
        for (int i = 0; i < token_list.size(); i++)
        {
            std::cout << Console::FgBrightBlue("[TOKEN]: ") << token_list[i].ToString() << "\n";
        }

        for (int i = 0; i < err.size(); i++)
        {
            std::cout << Console::FgBrightRed("[Error]: ") << err[i].ToString() << "\n";
        }
    }

    // AST::Function function;

    err.clear();
    AST::POUlist pou_list = Parse(err, token_list);

    for (int i = 0; i < err.size(); i++)
    {
        std::cout << Console::FgBrightRed("[Error]: ") << err[i].ToString() << "\n";
    }

    AST::CompilerContext cc;
    llvm::Function *fn = pou_list[0]->CodeGenLLVM(&cc);

    if (command_line.IsFlagUsed(CommandLineFlags::VERBOSE))
    {
        std::cout
            << Console::FgDarkGreen("[-------------------------------------------]: \n")
            << Console::FgDarkGreen("[Generated IR code]: \n")
            << cc.IR_ToString()
            << Console::FgDarkGreen("[End of Generated IR code]: \n")
            << Console::FgDarkGreen("[-------------------------------------------]: \n")
            << "\n";

        std::cout
            << Console::FgDarkGreen("[-------------------------------------------]: \n")
            << Console::FgDarkGreen("[Generated C/C++ header file]: \n")
            << pou_list[0]->CodeGenCHeader()
            << Console::FgDarkGreen("[End of Generated C/C++ header file]: \n")
            << Console::FgDarkGreen("[-------------------------------------------]: \n")
            << "\n";
    }
    // function.Evaluate();

    if (!command_line.IsFlagUsed(CommandLineFlags::OUTPUT_FILE))
    {
        std::cout << Console::FgBrightYellow("[Warning]: ") << "No output file specified\n";
    }else{
        // output code to file        
        std::string output_file_path = command_line.GetFlagArgs(CommandLineFlags::OUTPUT_FILE).front();
        std::string output_content = cc.IR_ToString();
        bool is_ok = WriteFileContent(output_file_path, output_content);
    }

    if (command_line.IsFlagUsed(CommandLineFlags::OUTPUT_C_HEADER))
    {
        std::string c_header_file_path = command_line.GetFlagArgs(CommandLineFlags::OUTPUT_C_HEADER).front();
        std::string c_header_content = pou_list[0]->CodeGenCHeader();
        bool is_ok = WriteFileContent(c_header_file_path, c_header_content);
    }

    return 0;
}
