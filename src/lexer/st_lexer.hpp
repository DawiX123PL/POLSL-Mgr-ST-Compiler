#pragma once

#include <vector>
#include <string>
#include <inttypes.h>
#include <utility>
#include "../error.hpp"
#include "st_token_type.hpp"

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

        Error::ErrorList_t Tokenize(const std::string &code, std::vector<Token> *tokens);

    typedef std::vector<Token> TokenList;

};
