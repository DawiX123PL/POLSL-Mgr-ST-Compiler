#include <string>
#include <iostream>
#include "lexer/st_lexer.hpp"
#include "file/file_utils.hpp"
#include "console/argument_parser.hpp"
#include "parser/st_parser.hpp"

int main(int argc, char **argv)
{

    std::map<ArgFlag, std::string> args = ArgsToMap(argc, argv);

    if (IsArgsContain(args, ArgFlag::Verbose))
    {
        PrintArgs(args);
    }

    std::string file_name = "./test/function1.st";
    //std::string file_name = "../test/function1.st";
    std::string file_content;
    bool isok = ReadFileContent(file_name, &file_content);

    if (isok)
    {
        PrintFileContent(file_content);

        std::vector<Lexer::Token> token_list;
        std::vector<Error> err = Lexer::Tokenize(file_content, &token_list);

        std::cout << Console::FgBrightBlue("[TOKEN COUNT]: ") << token_list.size() << "\n";
        for (int i = 0; i < token_list.size(); i++)
        {
            std::cout << Console::FgBrightBlue("[TOKEN]: ") << token_list[i].ToString() << "\n";
        }

        for (int i = 0; i < err.size(); i++)
        {
            std::cout << Console::FgBrightRed("[Error]: ") << err[i].ToString() << "\n";
        }

        AST::Function function;

        err = Parse(token_list, &function);

        for (int i = 0; i < err.size(); i++)
        {
            std::cout << Console::FgBrightRed("[Error]: ") << err[i].ToString() << "\n";
        }

        function.Evaluate();

    }
}
