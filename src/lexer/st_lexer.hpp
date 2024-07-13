#pragma once

#include <vector>
#include <string>
#include <inttypes.h>
#include <utility>
#include "../error.hpp"
#include "st_token_type.hpp"
#include "../file/file_utils.hpp"

namespace Lexer
{

    struct Token
    {

        TokenType type;
        std::string str;
        Position pos;

        Token() : type(TokenType::UNNOWN), str(), pos(0, 0) {}
        Token(TokenType _type, std::string _str) : type(_type), str(_str), pos(0, 0) {}
        Token(TokenType _type, std::string _str, Position _pos) : type(_type), str(_str), pos(_pos) {}

        std::string ToString()
        {
            if (type == TokenType::UNNOWN)
            {
                return pos.ToString() + " " + Console::FgDarkRed("UNNOWN:               ") + str;
            }

            if (type == TokenType::IDENTIFIER)
            {
                return pos.ToString() + " " + Console::FgBrightGreen("Identifier/Data Type: ") + str;
            }

            if (type == TokenType::NUMERIC_LITERAL)
            {
                return pos.ToString() + " " + Console::FgBrightBlue("Numeric Literal:      ") + str;
            }

            return pos.ToString() + " " + Console::FgBrightCyan("Keyword/Operator:     ") + Console::FgBrightCyan(TokenTypeToString(type)) + " " + str;
        }
    };

    typedef std::vector<Token> TokenList;

    
    std::vector<TokenList> TokenizeFiles(Error::ErrorList_t &err, const std::vector<File> files);
    TokenList Tokenize(Error::ErrorList_t &err, const std::string &code);

};
