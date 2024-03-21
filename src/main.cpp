#include <string>
#include <iostream>
#include "st_lexer.hpp"
#include "file_utils.hpp"
#include "argument_parser.hpp"



int main(int argc, char** argv){

    std::map<ArgFlag, std::string> args = ArgsToMap(argc, argv);

    if (IsArgsContain(args, ArgFlag::Verbose))
    {
        PrintArgs(args);
    }


    std::string file_content;

    bool isok = ReadFileContent("test/function1.st", &file_content);
    if(isok){
        PrintFileContent(file_content);

        std::vector<Token> tokens;
        Tokenize(file_content, &tokens);
    }

}



