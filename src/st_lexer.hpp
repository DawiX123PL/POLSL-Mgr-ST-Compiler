#pragma once

#include <vector>
#include <string>
#include <inttypes.h>
#include <utility>
#include "error.hpp"

struct Pos
{
    int line;
    int col;
    Pos(int _line, int _col) : line(_line), col(_col){};
};

struct Token
{
    Pos pos;
    std::string str;

    enum class TokenType
    {
        UNNOWN,
    };
};

constexpr std::pair<char *, Token::TokenType> keywords_list[] = {

    // comments
    {"//", Token::TokenType::UNNOWN},
    {"(*", Token::TokenType::UNNOWN},
    {"*)", Token::TokenType::UNNOWN},
    {"/*", Token::TokenType::UNNOWN},
    {"*/", Token::TokenType::UNNOWN},
    {"(*", Token::TokenType::UNNOWN},
    {"*)", Token::TokenType::UNNOWN},

    // Pragma
    {"{", Token::TokenType::UNNOWN},
    {"}", Token::TokenType::UNNOWN},

    // String Literals
    {"'", Token::TokenType::UNNOWN},
    {"\"", Token::TokenType::UNNOWN},

    // Numeric literals
    {"#", Token::TokenType::UNNOWN},

    // Bool Literals
    {"FALSE", Token::TokenType::UNNOWN},
    {"TRUE", Token::TokenType::UNNOWN},

    // ST operators
    {"(", Token::TokenType::UNNOWN},
    {")", Token::TokenType::UNNOWN},
    {"^", Token::TokenType::UNNOWN},
    {"-", Token::TokenType::UNNOWN},
    {"+", Token::TokenType::UNNOWN},
    {"NOT", Token::TokenType::UNNOWN},
    {"**", Token::TokenType::UNNOWN},
    {"*", Token::TokenType::UNNOWN},
    {"/", Token::TokenType::UNNOWN},
    {"MOD", Token::TokenType::UNNOWN},
    {">", Token::TokenType::UNNOWN},
    {"<", Token::TokenType::UNNOWN},
    {">=", Token::TokenType::UNNOWN},
    {"<=", Token::TokenType::UNNOWN},
    {"=", Token::TokenType::UNNOWN},
    {"<>", Token::TokenType::UNNOWN},
    {"&", Token::TokenType::UNNOWN},
    {"AND", Token::TokenType::UNNOWN},
    {"OR", Token::TokenType::UNNOWN},
    {"XOR", Token::TokenType::UNNOWN},

    //
    {"TYPE", Token::TokenType::UNNOWN},
    {"END_TYPE", Token::TokenType::UNNOWN},

    // variables
    {"VAR", Token::TokenType::UNNOWN},
    {"VAR_INPUT", Token::TokenType::UNNOWN},
    {"VAR_OUTPUT", Token::TokenType::UNNOWN},
    {"VAR_IN_OUT", Token::TokenType::UNNOWN},
    {"VAR_EXTERNAL", Token::TokenType::UNNOWN},
    {"VAR_TEMP", Token::TokenType::UNNOWN},
    {"VAR_ACCESS", Token::TokenType::UNNOWN},
    {"VAR_GLOBAL", Token::TokenType::UNNOWN},
    {"VAR_CONFIG", Token::TokenType::UNNOWN},
    {"END_VAR", Token::TokenType::UNNOWN},

    {"FUNCTION", Token::TokenType::UNNOWN},
    {"END_FUNCTION", Token::TokenType::UNNOWN},

    {"FUNCTION_BLOCK", Token::TokenType::UNNOWN},
    {"END_FUNCTION_BLOCK", Token::TokenType::UNNOWN},

    {"PROGRAM", Token::TokenType::UNNOWN},
    {"END_PROGRAM", Token::TokenType::UNNOWN},

    {"METHOD", Token::TokenType::UNNOWN},
    {"END_METHOD", Token::TokenType::UNNOWN},

    {"STEP", Token::TokenType::UNNOWN},
    {"END_STEP", Token::TokenType::UNNOWN},

    {"TRANSITION", Token::TokenType::UNNOWN},
    {"END_TRANSITION", Token::TokenType::UNNOWN},

    {"ACTION", Token::TokenType::UNNOWN},
    {"END_ACTION", Token::TokenType::UNNOWN},

    {"NAMESPACE", Token::TokenType::UNNOWN},
    {"END_NAMESPACE", Token::TokenType::UNNOWN},

};

constexpr int keywords_list_size = sizeof(keywords_list)/sizeof(keywords_list[0]);




std::vector<Error> Tokenize(const std::string &code, std::vector<Token> *tokens);
