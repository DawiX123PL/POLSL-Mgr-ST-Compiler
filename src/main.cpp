#include <string>
#include <iostream>
#include "lexer/st_lexer.hpp"
#include "file/file_utils.hpp"
#include "console/argument_parser.hpp"
#include "parser/parser.hpp"

int main(int argc, char **argv)
{

    std::map<ArgFlag, std::string> args = ArgsToMap(argc, argv);

    if (IsArgsContain(args, ArgFlag::Verbose))
    {
        PrintArgs(args);
    }

    // std::string file_name = "./test/function1.st";
    std::string file_name = "../test/function1.st";
    std::string file_content;
    bool isok = ReadFileContent(file_name, &file_content);

    if (!isok)
    {
        std::cout << Console::FgBrightRed("[Error]: ") << "cannot read file: " + file_name << "\n";
        return -1;
    }

    PrintFileContent(file_content);

    std::vector<Lexer::Token> token_list;
    ErrorList err;
    err = Lexer::Tokenize(file_content, &token_list);

    std::cout << Console::FgBrightBlue("[TOKEN COUNT]: ") << token_list.size() << "\n";
    for (int i = 0; i < token_list.size(); i++)
    {
        std::cout << Console::FgBrightBlue("[TOKEN]: ") << token_list[i].ToString() << "\n";
    }

    for (int i = 0; i < err.size(); i++)
    {
        std::cout << Console::FgBrightRed("[Error]: ") << err[i].ToString() << "\n";
    }

    // AST::Function function;

    err.clear();
    Parse(err, token_list);

    for (int i = 0; i < err.size(); i++)
    {
        std::cout << Console::FgBrightRed("[Error]: ") << err[i].ToString() << "\n";
    }

    // function.Evaluate();

    return 0;
}
