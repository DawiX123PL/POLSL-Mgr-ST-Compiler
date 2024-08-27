#pragma once

#include <filesystem>
#include "error_template.hpp"
#include "position.hpp"

#include "./frontend/lexer/st_token_type.hpp"
#include "./frontend/ast/type.hpp"

namespace Error
{

    //*****************************************************************************************************
    // Internal Compiler Error

    class InternalCompilerError : public BasicError
    {
        std::string message;

    public:
        InternalCompilerError(std::string _message) : message(_message) {};

        std::string MessageToString() const override
        {
            return std::string("Internal Compiler Error: ") + message;
        };
    };

    //*****************************************************************************************************
    // Syntax Error

    class SyntaxError : public BasicPosinionalError
    {
    public:
        SyntaxError();
        std::string MessageToString() const override
        {
            return "";
        };
    };

    //*****************************************************************************************************
    // Unexpected Token

    class UnexpectedTokenError : public BasicPosinionalError
    {
        Lexer::TokenType token;

    public:
        UnexpectedTokenError(Position _position, Lexer::TokenType _token)
            : BasicPosinionalError(_position),
              token(_token) {};

        std::string MessageToString() const override
        {
            return "Unexpected token (token: \'" + Lexer::TokenTypeToString(token) + ")";
        };
    };

    //*****************************************************************************************************
    // Unexpected Symbol

    class UnexpectedSymbolError : public BasicPosinionalError
    {

        unsigned char symbol;

    public:
        UnexpectedSymbolError(Position _position, unsigned char _symbol) : BasicPosinionalError(_position), symbol(_symbol) {};

        std::string MessageToString() const override
        {
            return "Unexpected symbol (Symbol: \'" + std::string(1, symbol) + "\'; ASCI code:" + std::to_string((int)symbol) + ")";
        };
    };

    //*****************************************************************************************************
    // Invalid Number with Given Base

    class InvalidNumberWithGivenBase : public BasicPosinionalError
    {
        // Position position; // TODO: push position with this error
        std::string number;
        int base;

    public:
        InvalidNumberWithGivenBase(Position _position, std::string _number, int _base) : BasicPosinionalError(_position), number(_number), base(_base) {};

        std::string MessageToString() const override
        {
            return "Number :" + number + " is not valid base " + std::to_string(base) + " number.";
        };
    };

    //*****************************************************************************************************
    // Missing Function Closing Tag

    class MissingFunctionClosingTag : public BasicPosinionalError
    {
        // Position position; // TODO: push position with this error

    public:
        MissingFunctionClosingTag(Position _position) : BasicPosinionalError(_position) {};

        std::string MessageToString() const override
        {
            return "Missing END_FUNCTION at the end of FUNCTION";
        };
    };

    //*****************************************************************************************************
    // Missing Function Block Closing Tag

    class MissingFunctionBlockClosingTag : public BasicPosinionalError
    {

    public:
        MissingFunctionBlockClosingTag(Position _position) : BasicPosinionalError(_position) {};

        std::string MessageToString() const override
        {
            return "Missing END_FUNCTION_BLOCK at the end of FUNCTION_BLOCK";
        };
    };

    //*****************************************************************************************************
    // Missing Program Closing Tag

    class MissingProgramClosingTag : public BasicPosinionalError
    {

    public:
        MissingProgramClosingTag(Position _position) : BasicPosinionalError(_position) {};

        std::string MessageToString() const override
        {
            return "Missing END_PROGRAM at the end of PROGRAM";
        };
    };

    //*****************************************************************************************************
    // Expected Function Keyword

    class ExpectedKeyword : public BasicPosinionalError
    {

        Lexer::TokenType keyword;

    public:
        ExpectedKeyword(Position _position, Lexer::TokenType _keyword) : BasicPosinionalError(_position), keyword(_keyword) {};

        std::string MessageToString() const override
        {
            return std::string("Expected token \"") + Lexer::TokenTypeToString(keyword);
        };
    };

    //*****************************************************************************************************
    // Invalid Data Type

    class InvalidDataType : public BasicPosinionalError
    {

        std::string type;

    public:
        InvalidDataType(Position _position, std::string _type) : BasicPosinionalError(_position), type(_type) {};

        std::string MessageToString() const override
        {
            return "Invalid data type (\"" + type + "\")";
        };
    };

    //*****************************************************************************************************
    // Missing Keyword After previous keyword

    class MissingKeywordAfter : public BasicPosinionalError
    {

        Lexer::TokenType starting_keyword;
        Lexer::TokenType missing_keyword;

    public:
        MissingKeywordAfter(Position _position, Lexer::TokenType _starting_keyword, Lexer::TokenType _missing_keyword)
            : BasicPosinionalError(_position), starting_keyword(_starting_keyword), missing_keyword(_missing_keyword) {};

        std::string MessageToString() const override
        {
            return std::string("Missing ") + Lexer::TokenTypeToString(missing_keyword) + " after " + Lexer::TokenTypeToString(starting_keyword);
        };
    };

    //*****************************************************************************************************
    // Missing Keyword After previous keyword

    class MissingKeyword : public BasicPosinionalError
    {

        Lexer::TokenType missing_keyword;

    public:
        MissingKeyword(Position _position, Lexer::TokenType _missing_keyword)
            : BasicPosinionalError(_position), missing_keyword(_missing_keyword) {};

        std::string MessageToString() const override
        {
            return std::string("Missing ") + Lexer::TokenTypeToString(missing_keyword);
        };
    };

    //*****************************************************************************************************
    // Missing Keyword After previous keyword

    class ExpectedIdentifier : public BasicPosinionalError
    {
        std::string description;

    public:
        ExpectedIdentifier(Position _position, std::string _description)
            : BasicPosinionalError(_position),
              description(_description) {};

        std::string MessageToString() const override
        {
            if (description.empty())
            {
                return "Expected Identifier";
            }
            else
            {
                return "Expected Identifier (" + description + ")";
            }
        };
    };

    //*****************************************************************************************************
    // Invalid Expresion

    class InvalidExpresion : public BasicPosinionalError
    {

    public:
        InvalidExpresion(Position _position)
            : BasicPosinionalError(_position) {};

        std::string MessageToString() const override
        {
            return "Invalid Expresion";
        };
    };

    //*****************************************************************************************************
    // Invalid Numeric Literal

    class InvalidNumericLiteral : public BasicPosinionalError
    {

    public:
        InvalidNumericLiteral(Position _position)
            : BasicPosinionalError(_position) {};

        std::string MessageToString() const override
        {
            return "Invalid Numeric Literal";
        };
    };

    //*****************************************************************************************************
    // Literal Base Range

    class LiteralBaseRange : public BasicPosinionalError
    {

    public:
        LiteralBaseRange(Position _position)
            : BasicPosinionalError(_position) {};

        std::string MessageToString() const override
        {
            return "Literal base must be in range [2, 36]";
        };
    };

    //*****************************************************************************************************
    // Illegal Bool Value

    class IllegalBoolValue : public BasicPosinionalError
    {

    public:
        IllegalBoolValue(Position _position)
            : BasicPosinionalError(_position) {};

        std::string MessageToString() const override
        {
            return "BOOL literal must be 0 (FALSE) or 1 (TRUE)";
        };
    };

    class InvalidGlobalAddress : public BasicPosinionalError
    {

    public:
        InvalidGlobalAddress(Position _position)
            : BasicPosinionalError(_position) {};

        std::string MessageToString() const override
        {
            return "Invalid memory address";
        };
    };

    class InvalidBinaryOperation : public BasicPosinionalError
    {
        std::string operation;
        AST::Type left;
        AST::Type right;

    public:
        InvalidBinaryOperation(Position _position, std::string _operation, AST::Type _left, AST::Type _right)
            : BasicPosinionalError(_position),
              operation(_operation),
              left(_left),
              right(_right) {};

        std::string MessageToString() const override
        {
            return "Cannot perfom operation '" + operation + "' on types " + left.ToString() + " and " + right.ToString();
        };
    };

    class InvalidUnaryOperation : public BasicPosinionalError
    {
        std::string operation;
        AST::Type type;

    public:
        InvalidUnaryOperation(Position _position, std::string _operation, AST::Type _type)
            : BasicPosinionalError(_position),
              operation(_operation),
              type(_type) {};

        std::string MessageToString() const override
        {
            return "Cannot perfom operation '" + operation + "' type " + type.ToString();
        };
    };

    class ConditionShouldBeBool : public BasicPosinionalError
    {
        AST::Type type;

    public:
        ConditionShouldBeBool(Position _position, AST::Type _type)
            : BasicPosinionalError(_position),
              type(_type) {};

        std::string MessageToString() const override
        {
            return "Condidion should be of type BOOL but found: " + type.ToString();
        };
    };

    class UndefinedVariable : public BasicPosinionalError
    {
        std::string name;
    public:
        UndefinedVariable(Position _position, std::string _name)
            : BasicPosinionalError(_position), name(_name) {};

        std::string MessageToString() const override
        {
            return "Undefined variable '" + name + "'";
        };
    };

    class InvalidLiteralType : public BasicPosinionalError
    {
    public:
        InvalidLiteralType(Position _position)
            : BasicPosinionalError(_position){};

        std::string MessageToString() const override
        {
            return "Invalid Literal Type";
        };
    };

    class InvalidMemoryAddress : public BasicPosinionalError
    {
    public:
        InvalidMemoryAddress(Position _position)
            : BasicPosinionalError(_position){};

        std::string MessageToString() const override
        {
            return "Invalid memory address";
        };
    };


    //*****************************************************************************************************
    // Cannot Read/write File

    class CannotReadFile : public BasicError
    {
        std::filesystem::path path;

    public:
        CannotReadFile(std::filesystem::path _path)
            : path(_path) {};

        std::string MessageToString() const override
        {
            return "Cannot Read file content : " + path.string();
        };
    };

    class CannotWriteFile : public BasicError
    {
        std::string path;

    public:
        CannotWriteFile(std::string _path)
            : path(_path) {};

        std::string MessageToString() const override
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
        NoInputFiles() {};

        std::string MessageToString() const override
        {
            return "No Input Files";
        };
    };

}
