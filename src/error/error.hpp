#pragma once

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "console/color.hpp"
#include "position.hpp"
#include "frontend/lexer/st_token_type.hpp"



namespace Error
{
    class BasicError
    {
    public:
        virtual std::string ToString() const = 0;
    };

    std::ostream &operator<<(std::ostream &os, BasicError const &error);

    //*****************************************************************************************************
    // Error List

    typedef std::vector<std::shared_ptr<BasicError>> ErrorList_t;

    //*****************************************************************************************************
    // helper function for pushing error objects to list

    template <typename T>
    void PushError(ErrorList_t &error_list, const T error)
    {
        error_list.push_back(std::make_shared<T>(error));
    }

    //*****************************************************************************************************
    // helper function for pushing error objects to list

    void PrintErrors(const Error::ErrorList_t &error_list);

    //*****************************************************************************************************
    // Internal Compiler Error

    class InternalCompilerError : public BasicError
    {
        std::string message;

    public:
        InternalCompilerError(std::string _message) : message(_message){};

        std::string ToString() const override
        {
            return std::string("Internal Compiler Error: ") + message;
        };
    };

    //*****************************************************************************************************
    // Syntax Error

    class SyntaxError : public BasicError
    {
    public:
        SyntaxError();
        std::string ToString() const override
        {
            return "";
        };
    };

    //*****************************************************************************************************
    // Unexpected Token

    class UnexpectedTokenError : public BasicError
    {
        Position position;
        Lexer::TokenType token;

    public:
        UnexpectedTokenError(Position _position, Lexer::TokenType _token) : position(_position), token(_token){};

        std::string ToString() const override
        {
            return "Unexpected token at position " + position.ToString() + " (token: \'" + Lexer::TokenTypeToString(token) + ")";
        };
    };

    //*****************************************************************************************************
    // Unexpected Symbol

    class UnexpectedSymbolError : public BasicError
    {
        Position position;
        unsigned char symbol;

    public:
        UnexpectedSymbolError(Position _position, unsigned char _symbol) : position(_position), symbol(_symbol){};

        std::string ToString() const override
        {
            return "Unexpected symbol at position " + position.ToString() + " (Symbol: \'" + std::string(1, symbol) + "\'; ASCI code:" + std::to_string((int)symbol) + ")";
        };
    };

    //*****************************************************************************************************
    // Invalid Number with Given Base

    class InvalidNumberWithGivenBase : public BasicError
    {
        // Position position; // TODO: push position with this error
        std::string number;
        int base;

    public:
        InvalidNumberWithGivenBase(std::string _number, int _base) : number(_number), base(_base){};

        std::string ToString() const override
        {
            return "Number :" + number + " is not valid base " + std::to_string(base) + " number.";
        };
    };

    //*****************************************************************************************************
    // Missing Function Closing Tag

    class MissingFunctionClosingTag : public BasicError
    {
        // Position position; // TODO: push position with this error
        Position position;

    public:
        MissingFunctionClosingTag(Position _position) : position(_position){};

        std::string ToString() const override
        {
            return "Missing END_FUNCTION at the end of FUNCTION, starting from " + position.ToString();
        };
    };

    //*****************************************************************************************************
    // Missing Function Block Closing Tag

    class MissingFunctionBlockClosingTag : public BasicError
    {
        Position position;

    public:
        MissingFunctionBlockClosingTag(Position _position) : position(_position){};

        std::string ToString() const override
        {
            return "Missing END_FUNCTION_BLOCK at the end of FUNCTION_BLOCK, starting from " + position.ToString();
        };
    };

    //*****************************************************************************************************
    // Missing Program Closing Tag

    class MissingProgramClosingTag : public BasicError
    {
        Position position;

    public:
        MissingProgramClosingTag(Position _position) : position(_position){};

        std::string ToString() const override
        {
            return "Missing END_PROGRAM at the end of PROGRAM, starting from " + position.ToString();
        };
    };

    //*****************************************************************************************************
    // Expected Function Keyword

    class ExpectedKeyword : public BasicError
    {
        Position position;
        Lexer::TokenType keyword;

    public:
        ExpectedKeyword(Position _position, Lexer::TokenType _keyword) : position(_position), keyword(_keyword){};

        std::string ToString() const override
        {
            return std::string("Expected token \"") + Lexer::TokenTypeToString(keyword) + "\" at: " + position.ToString();
        };
    };

    //*****************************************************************************************************
    // Invalid Data Type

    class InvalidDataType : public BasicError
    {
        Position position;
        std::string type;

    public:
        InvalidDataType(Position _position, std::string _type) : position(_position), type(_type){};

        std::string ToString() const override
        {
            return "Invalid data type (\"" + type + "\") at position " + position.ToString();
        };
    };

    //*****************************************************************************************************
    // Missing Keyword After previous keyword

    class MissingKeywordAfter : public BasicError
    {
        Position position;
        Lexer::TokenType starting_keyword;
        Lexer::TokenType missing_keyword;

    public:
        MissingKeywordAfter(Position _position, Lexer::TokenType _starting_keyword, Lexer::TokenType _missing_keyword)
            : position(_position), starting_keyword(_starting_keyword), missing_keyword(_missing_keyword){};

        std::string ToString() const override
        {
            return std::string("Missing ") + Lexer::TokenTypeToString(missing_keyword) + " after " + Lexer::TokenTypeToString(starting_keyword) + "at: " + position.ToString();
        };
    };

    //*****************************************************************************************************
    // Missing Keyword After previous keyword

    class MissingKeyword : public BasicError
    {
        Position position;
        Lexer::TokenType missing_keyword;

    public:
        MissingKeyword(Position _position, Lexer::TokenType _missing_keyword)
            : position(_position), missing_keyword(_missing_keyword){};

        std::string ToString() const override
        {
            return std::string("Missing ") + Lexer::TokenTypeToString(missing_keyword) + "at: " + position.ToString();
        };
    };

    //*****************************************************************************************************
    // Missing Keyword After previous keyword

    class ExpectedIdentifier : public BasicError
    {
        Position position;
        std::string description;

    public:
        ExpectedIdentifier(Position _position, std::string _description)
            : position(_position), description(_description){};

        std::string ToString() const override
        {
            if (description.empty())
            {
                return "Expected Identifier at" + position.ToString();
            }
            else
            {
                return "Expected Identifier at" + position.ToString() + "(" + description + ")";
            }
        };
    };

    //*****************************************************************************************************
    // Invalid Expresion

    class InvalidExpresion : public BasicError
    {
        Position position;

    public:
        InvalidExpresion(Position _position)
            : position(_position){};

        std::string ToString() const override
        {
            return "Invalid Expresion at position" + position.ToString();
        };
    };

    //*****************************************************************************************************
    // Invalid Numeric Literal

    class InvalidNumericLiteral : public BasicError
    {
        Position position;

    public:
        InvalidNumericLiteral(Position _position)
            : position(_position){};

        std::string ToString() const override
        {
            return "Invalid Numeric Literal at position" + position.ToString();
        };
    };

    //*****************************************************************************************************
    // Literal Base Range

    class LiteralBaseRange : public BasicError
    {
        Position position;

    public:
        LiteralBaseRange(Position _position)
            : position(_position){};

        std::string ToString() const override
        {
            return "Literal base must be in range [2, 36], (at position: " + position.ToString() + ")";
        };
    };

    //*****************************************************************************************************
    // Illegal Bool Value

    class IllegalBoolValue : public BasicError
    {
        Position position;

    public:
        IllegalBoolValue(Position _position)
            : position(_position){};

        std::string ToString() const override
        {
            return "BOOL literal must be 0 (FALSE) or 1 (TRUE), at:" + position.ToString();
        };
    };

    //*****************************************************************************************************
    // Cannot Read File 

    class CannotReadFile : public BasicError
    {
        std::string path;

    public:
        CannotReadFile(std::string _path)
            : path(_path){};

        std::string ToString() const override
        {
            return "Cannot Read file content : " + path;
        };
    };

    //*****************************************************************************************************
    // No Input Files 

    class NoInputFiles : public BasicError
    {
        std::string path;

    public:
        NoInputFiles(){};

        std::string ToString() const override
        {
            return "No Input Files";
        };
    };

};
