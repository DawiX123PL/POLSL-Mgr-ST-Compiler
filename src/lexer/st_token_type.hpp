#pragma once

#include <utility>

namespace Lexer
{

    enum class TokenType
    {
        UNNOWN, // error case

        IDENTIFIER,

        NUMERIC_LITERAL,

        // comments
        COMMENT_ONELINE,
        COMMENT_MULTILINE_BRACKET_OPEN,
        COMMENT_MULTILINE_BRACKET_CLOSE,
        COMMENT_MULTILINE_SLASH_OPEN,
        COMMENT_MULTILINE_SLASH_CLOSE,

        // Pragma
        PRAGMA_OPEN,
        PRAGMA_CLOSE,

        // String Literals
        QUOTATION_MARK_SINGLE,
        QUOTATION_MARK_DOUBLE,

        // Numeric literals
        NUMBER_SIGN,

        // Bool Literals
        FALSE,
        TRUE,

        // ST operators
        ROUND_BRACKET_OPENING,
        ROUND_BRACKET_CLOSING,
        SQUARE_BRACKET_OPENING,
        SQUARE_BRACKET_CLOSING,

        DOUBLE_DOT,
        DOT,
        COMMA,
        DEREFERENCE,
        MINUS,
        PLUS,
        NEGATION,
        EXPONENTIATION,
        MULTIPLY,
        DIVIDE,
        MODULO,
        GREATER_THAN,
        LESS_THAN,
        GREATER_OR_EQUAL,
        LESS_OR_EQUAL,
        EQUALITY,
        INEQUALITY,
        BOOLEAN_AND,
        BOOLEAN_XOR,
        BOOLEAN_OR,
        ASSIGN,
        COLON,
        SEMICOLON,
        RETURN,

        // conditionals and loops
        IF,
        THEN,
        ELSIF,
        ELSE,
        END_IF,
        CASE,
        OF,
        END_CASE,

        FOR,
        TO,
        BY,
        DO,
        END_FOR,
        WHILE,
        END_WHILE,
        REPEAT,
        UNTIL,
        END_REPEAT,
        CONTINUE,
        EXIT,

        //
        TYPE,
        END_TYPE,

        // variables
        VAR,
        VAR_INPUT,
        VAR_OUTPUT,
        VAR_IN_OUT,
        VAR_EXTERNAL,
        VAR_TEMP,
        VAR_ACCESS,
        VAR_GLOBAL,
        VAR_CONFIG,
        END_VAR,

        FUNCTION,
        END_FUNCTION,

        FUNCTION_BLOCK,
        END_FUNCTION_BLOCK,

        PROGRAM,
        END_PROGRAM,

        METHOD,
        END_METHOD,

        STEP,
        END_STEP,

        TRANSITION,
        END_TRANSITION,

        ACTION,
        END_ACTION,

        NAMESPACE,
        END_NAMESPACE,
    };

    constexpr std::pair<const char *, TokenType> tokentype_names_list[] = {
        {"UNNOWN", TokenType::UNNOWN}, // error case,
        {"IDENTIFIER", TokenType::IDENTIFIER},
        {"NUMERIC_LITERAL", TokenType::NUMERIC_LITERAL},
        {"COMMENT_ONELINE", TokenType::COMMENT_ONELINE},
        {"COMMENT_MULTILINE_BRACKET_OPEN", TokenType::COMMENT_MULTILINE_BRACKET_OPEN},
        {"COMMENT_MULTILINE_BRACKET_CLOSE", TokenType::COMMENT_MULTILINE_BRACKET_CLOSE},
        {"COMMENT_MULTILINE_SLASH_OPEN", TokenType::COMMENT_MULTILINE_SLASH_OPEN},
        {"COMMENT_MULTILINE_SLASH_CLOSE", TokenType::COMMENT_MULTILINE_SLASH_CLOSE},
        {"PRAGMA_OPEN", TokenType::PRAGMA_OPEN},
        {"PRAGMA_CLOSE", TokenType::PRAGMA_CLOSE},
        {"QUOTATION_MARK_SINGLE", TokenType::QUOTATION_MARK_SINGLE},
        {"QUOTATION_MARK_DOUBLE", TokenType::QUOTATION_MARK_DOUBLE},
        {"NUMBER_SIGN", TokenType::NUMBER_SIGN},
        {"FALSE", TokenType::FALSE},
        {"TRUE", TokenType::TRUE},
        {"ROUND_BRACKET_OPENING", TokenType::ROUND_BRACKET_OPENING},
        {"ROUND_BRACKET_CLOSING", TokenType::ROUND_BRACKET_CLOSING},
        {"DEREFERENCE", TokenType::DEREFERENCE},
        {"MINUS", TokenType::MINUS},
        {"PLUS", TokenType::PLUS},
        {"NEGATION", TokenType::NEGATION},
        {"EXPONENTIATION", TokenType::EXPONENTIATION},
        {"MULTIPLY", TokenType::MULTIPLY},
        {"DIVIDE", TokenType::DIVIDE},
        {"MODULO", TokenType::MODULO},
        {"GREATER_THAN", TokenType::GREATER_THAN},
        {"LESS_THAN", TokenType::LESS_THAN},
        {"GREATER_OR_EQUAL", TokenType::GREATER_OR_EQUAL},
        {"LESS_OR_EQUAL", TokenType::LESS_OR_EQUAL},
        {"EQUALITY", TokenType::EQUALITY},
        {"INEQUALITY", TokenType::INEQUALITY},
        {"BOOLEAN_AND", TokenType::BOOLEAN_AND},
        {"BOOLEAN_XOR", TokenType::BOOLEAN_XOR},
        {"BOOLEAN_OR", TokenType::BOOLEAN_OR},
        {"ASSIGN", TokenType::ASSIGN},
        {"COLON", TokenType::COLON},
        {"SEMICOLON", TokenType::SEMICOLON},
        {"RETURN", TokenType::RETURN},
        {"IF", TokenType::IF},
        {"THEN", TokenType::THEN},
        {"ELSIF", TokenType::ELSIF},
        {"ELSE", TokenType::ELSE},
        {"END_IF", TokenType::END_IF},
        {"CASE", TokenType::CASE},
        {"OF", TokenType::OF},
        {"END_CASE", TokenType::END_CASE},
        {"FOR", TokenType::FOR},
        {"TO", TokenType::TO},
        {"BY", TokenType::BY},
        {"DO", TokenType::DO},
        {"END_FOR", TokenType::END_FOR},
        {"WHILE", TokenType::WHILE},
        {"END_WHILE", TokenType::END_WHILE},
        {"REPEAT", TokenType::REPEAT},
        {"UNTIL", TokenType::UNTIL},
        {"END_REPEAT", TokenType::END_REPEAT},
        {"CONTINUE", TokenType::CONTINUE},
        {"EXIT", TokenType::EXIT},
        {"TYPE", TokenType::TYPE},
        {"END_TYPE", TokenType::END_TYPE},
        {"VAR", TokenType::VAR},
        {"VAR_INPUT", TokenType::VAR_INPUT},
        {"VAR_OUTPUT", TokenType::VAR_OUTPUT},
        {"VAR_IN_OUT", TokenType::VAR_IN_OUT},
        {"VAR_EXTERNAL", TokenType::VAR_EXTERNAL},
        {"VAR_TEMP", TokenType::VAR_TEMP},
        {"VAR_ACCESS", TokenType::VAR_ACCESS},
        {"VAR_GLOBAL", TokenType::VAR_GLOBAL},
        {"VAR_CONFIG", TokenType::VAR_CONFIG},
        {"END_VAR", TokenType::END_VAR},
        {"FUNCTION", TokenType::FUNCTION},
        {"END_FUNCTION", TokenType::END_FUNCTION},
        {"FUNCTION_BLOCK", TokenType::FUNCTION_BLOCK},
        {"END_FUNCTION_BLOCK", TokenType::END_FUNCTION_BLOCK},
        {"PROGRAM", TokenType::PROGRAM},
        {"END_PROGRAM", TokenType::END_PROGRAM},
        {"METHOD", TokenType::METHOD},
        {"END_METHOD", TokenType::END_METHOD},
        {"STEP", TokenType::STEP},
        {"END_STEP", TokenType::END_STEP},
        {"TRANSITION", TokenType::TRANSITION},
        {"END_TRANSITION", TokenType::END_TRANSITION},
        {"ACTION", TokenType::ACTION},
        {"END_ACTION", TokenType::END_ACTION},
        {"NAMESPACE", TokenType::NAMESPACE},
        {"END_NAMESPACE", TokenType::END_NAMESPACE},
    };

    constexpr std::pair<const char *, TokenType> keywords_list[] = {

        // comments
        {"//", TokenType::COMMENT_ONELINE},
        {"(*", TokenType::COMMENT_MULTILINE_BRACKET_OPEN},
        {"*)", TokenType::COMMENT_MULTILINE_BRACKET_CLOSE},
        {"/*", TokenType::COMMENT_MULTILINE_SLASH_OPEN},
        {"*/", TokenType::COMMENT_MULTILINE_SLASH_CLOSE},

        // Pragma
        {"{", TokenType::PRAGMA_OPEN},
        {"}", TokenType::PRAGMA_CLOSE},

        // String Literals
        {"'", TokenType::QUOTATION_MARK_SINGLE},
        {"\"", TokenType::QUOTATION_MARK_DOUBLE},

        // Numeric literals
        {"#", TokenType::NUMBER_SIGN},

        // Bool Literals
        {"FALSE", TokenType::FALSE},
        {"TRUE", TokenType::TRUE},

        // ST operators
        {"(", TokenType::ROUND_BRACKET_OPENING},
        {")", TokenType::ROUND_BRACKET_CLOSING},
        {"^", TokenType::DEREFERENCE},
        {"-", TokenType::MINUS},
        {"+", TokenType::PLUS},
        {"NOT", TokenType::NEGATION},
        {"**", TokenType::EXPONENTIATION},
        {"*", TokenType::MULTIPLY},
        {"/", TokenType::DIVIDE},
        {"MOD", TokenType::MODULO},
        {">", TokenType::GREATER_THAN},
        {"<", TokenType::LESS_THAN},
        {">=", TokenType::GREATER_OR_EQUAL},
        {"<=", TokenType::LESS_OR_EQUAL},
        {"=", TokenType::EQUALITY},
        {"<>", TokenType::INEQUALITY},
        {"&", TokenType::BOOLEAN_AND},
        {"AND", TokenType::BOOLEAN_AND},
        {"XOR", TokenType::BOOLEAN_XOR},
        {"OR", TokenType::BOOLEAN_OR},
        {":=", TokenType::ASSIGN},
        {":", TokenType::COLON},
        {";", TokenType::SEMICOLON},
        {"RETURN", TokenType::RETURN},

        // conditionals and loops
        {"IF", TokenType::IF},
        {"THEN", TokenType::THEN},
        {"ELSIF", TokenType::ELSIF},
        {"ELSE", TokenType::ELSE},
        {"END_IF", TokenType::END_IF},
        {"CASE", TokenType::CASE},
        {"OF", TokenType::OF},
        {"END_CASE", TokenType::END_CASE},

        {"FOR", TokenType::FOR},
        {"TO", TokenType::TO},
        {"BY", TokenType::BY},
        {"DO", TokenType::DO},
        {"END_FOR", TokenType::END_FOR},
        {"WHILE", TokenType::WHILE},
        {"END_WHILE", TokenType::END_WHILE},
        {"REPEAT", TokenType::REPEAT},
        {"UNTIL", TokenType::UNTIL},
        {"END_REPEAT", TokenType::END_REPEAT},
        {"CONTINUE", TokenType::CONTINUE},
        {"EXIT", TokenType::EXIT},

        //
        {"TYPE", TokenType::TYPE},
        {"END_TYPE", TokenType::END_TYPE},

        // variables
        {"VAR", TokenType::VAR},
        {"VAR_INPUT", TokenType::VAR_INPUT},
        {"VAR_OUTPUT", TokenType::VAR_OUTPUT},
        {"VAR_IN_OUT", TokenType::VAR_IN_OUT},
        {"VAR_EXTERNAL", TokenType::VAR_EXTERNAL},
        {"VAR_TEMP", TokenType::VAR_TEMP},
        {"VAR_ACCESS", TokenType::VAR_ACCESS},
        {"VAR_GLOBAL", TokenType::VAR_GLOBAL},
        {"VAR_CONFIG", TokenType::VAR_CONFIG},
        {"END_VAR", TokenType::END_VAR},

        {"FUNCTION", TokenType::FUNCTION},
        {"END_FUNCTION", TokenType::END_FUNCTION},

        {"FUNCTION_BLOCK", TokenType::FUNCTION_BLOCK},
        {"END_FUNCTION_BLOCK", TokenType::END_FUNCTION_BLOCK},

        {"PROGRAM", TokenType::PROGRAM},
        {"END_PROGRAM", TokenType::END_PROGRAM},

        {"METHOD", TokenType::METHOD},
        {"END_METHOD", TokenType::END_METHOD},

        {"STEP", TokenType::STEP},
        {"END_STEP", TokenType::END_STEP},

        {"TRANSITION", TokenType::TRANSITION},
        {"END_TRANSITION", TokenType::END_TRANSITION},

        {"ACTION", TokenType::ACTION},
        {"END_ACTION", TokenType::END_ACTION},

        {"NAMESPACE", TokenType::NAMESPACE},
        {"END_NAMESPACE", TokenType::END_NAMESPACE},

    };

    const char *TokenTypeToString(TokenType type);

}
