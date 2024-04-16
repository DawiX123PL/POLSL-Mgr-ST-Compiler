#include <string>
#include <iostream>
#include "lexer/st_lexer.hpp"
#include "file/file_utils.hpp"
#include "console/argument_parser.hpp"
#include "parser/parser.hpp"

int main(int argc, char **argv)
{

    ArgumentParser args_parser;
    args_parser.Parse(argc, argv);

    if (args_parser.GetFreeArguments().size() == 0)
    {
        std::cout << Console::FgBrightRed("[Error]: ") << "No input files\n";
        return -1;
    }

    if (args_parser.GetFreeArguments().size() == 0)
    {
        std::cout << Console::FgBrightYellow("[Warning]: ") << "More than one file provided. Ignoring extra files\n";
    }

    std::string input_file_name = args_parser.GetFreeArguments().front();

    std::string file_content;
    bool isok = ReadFileContent(input_file_name, &file_content);

    if (!isok)
    {
        std::cout << Console::FgBrightRed("[Error]: ") << "cannot read file: \"" + input_file_name << "\" \n";
        return -1;
    }

    if (args_parser.HaveFlag(ArgumentParser::Flags::Verbose))
    {
        PrintFileContent(file_content);
    }

    std::vector<Lexer::Token> token_list;
    ErrorList_t err;
    err = Lexer::Tokenize(file_content, &token_list);

    if (args_parser.HaveFlag(ArgumentParser::Flags::Verbose))
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

    if (args_parser.HaveFlag(ArgumentParser::Flags::Verbose))
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

    if (!args_parser.HaveFlag(ArgumentParser::Flags::Output))
    {
        std::cout << Console::FgBrightYellow("[Warning]: ") << "No output file specified\n";
    }else{
        // output code to file
        std::string output_file_path = args_parser.GetFlags().at(ArgumentParser::Flags::Output);
        std::string output_content = cc.IR_ToString();
        bool is_ok = WriteFileContent(output_file_path, output_content);
    }

    if (args_parser.HaveFlag(ArgumentParser::Flags::OutputCHeader))
    {
        std::string c_header_file_path = args_parser.GetFlags().at(ArgumentParser::Flags::OutputCHeader);
        std::string c_header_content = pou_list[0]->CodeGenCHeader();
        bool is_ok = WriteFileContent(c_header_file_path, c_header_content);
    }

    return 0;
}
