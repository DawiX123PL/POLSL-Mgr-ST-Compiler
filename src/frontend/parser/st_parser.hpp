#pragma once

#include <utility>
#include "st_expression_parser.hpp"
#include "error/error_manager.hpp"
#include "frontend/lexer/st_lexer.hpp"
#include "frontend/ast/ast1.hpp"

namespace StParser
{

    //*********************************
    // Utility Function / helper function

    template <class V>
    bool IsIndexInBounds(const V &vec, int index)
    {
        return (index >= 0) && (index < vec.size());
    }

    // Finds token pair of specified types
    // returns -1 in case of failure
    std::pair<int, int> FindTokenPair(const Lexer::TokenList &tokens, Lexer::TokenType first, Lexer::TokenType second);

    // Finds token of specified type
    // returns -1 in case of failure
    int FindToken(const Lexer::TokenList &tokens, Lexer::TokenType type);

    // Finds token of specified type (starting from index `start`)
    // returns -1 in case of failure
    int FindToken(const Lexer::TokenList &tokens, int start, Lexer::TokenType type);

    // Returns list of tokens with indexes <first, second>.
    // Negative numbers are indexes counting from second element (second = -1);
    //
    Lexer::TokenList Split(const Lexer::TokenList &tokens, int first, int second);

    // Returns list of tokens with indexes <first, second>.
    // Negative numbers are indexes counting from second element (second = -1);
    //
    Lexer::TokenList Split(const Lexer::TokenList &tokens, std::pair<int, int> index);

    // check if token with specified type is at index
    bool IsTokenTypeAt(Lexer::TokenList &tokens, int index, Lexer::TokenType type);

    // checks if token exists in specified index
    // if not, return false and pushes error
    bool ExpectToken(const Lexer::TokenList &tokens, int index, Lexer::TokenType type);

    //
    // Finds token and ignores everything between `nested_ignored.first` and `nested_ignored.second`
    //
    //
    int FindTokenAndIgnoreNeasted(const Lexer::TokenList &tokens, Lexer::TokenType searched_token, std::pair<Lexer::TokenType, Lexer::TokenType> nested_ignored);

    //
    // Finds token (sterting from specified index) and ignores everything between `nested_ignored.first` and `nested_ignored.second`
    //
    //
    int FindTokenAndIgnoreNeasted(const Lexer::TokenList &tokens, int start_index, Lexer::TokenType searched_token, std::pair<Lexer::TokenType, Lexer::TokenType> nested_ignored);

    //
    // Finds token (sterting from specified index) and ignores everything between `nested_ignored.first` and `nested_ignored.second`
    //
    // returns finded token with index
    // or index = -1 if token not found
    std::pair<int, Lexer::TokenType> FindTokenAndIgnoreNeasted(const Lexer::TokenList &tokens, int start_index, std::initializer_list<Lexer::TokenType> searched_tokens, std::pair<Lexer::TokenType, Lexer::TokenType> nested_ignored);

    //*********************************
    // helper classes

    struct AllVars
    {
        AST::VarList input;
        AST::VarList output;
        AST::VarList input_output;
        AST::VarList var;
    };

    struct PouBody
    {
        AllVars vars;
        AST::StmtList stmt_list;
    };

    //*********************************
    // parsing functions

    // Parses whole file content
    AST::PouList
    Parse(Lexer::TokenList tokens, bool IsExtern);

    AST::PouPtr ParseFunction(Lexer::TokenList tokens, bool IsExtern);
    AST::PouPtr ParseFunctionBlock(Lexer::TokenList tokens, bool IsExtern);
    AST::PouPtr ParseProgram(Lexer::TokenList tokens, bool IsExtern);

    PouBody ParsePouBody(Lexer::TokenList tokens);
    AST::VarList ParseVarBody(Lexer::TokenList tokens);

    AllVars ParseAllVars(Lexer::TokenList tokens, int *last_position);
    AST::VarList ParseVar(Lexer::TokenList tokens);
    AST::VarList ParseVarInput(Lexer::TokenList tokens);
    AST::VarList ParseVarInOut(Lexer::TokenList tokens);
    AST::VarList ParseVarOutput(Lexer::TokenList tokens);
    AST::Variable ParseVariableDeclaration(Lexer::TokenList tokens);

    AST::StmtList ParseStatementList(Lexer::TokenList tokens);
    AST::StmtPtr ParseStatement(Lexer::TokenList tokens);
    AST::StmtPtr ParseForStatement(Lexer::TokenList tokens);
    AST::StmtPtr ParseWhileStatement(Lexer::TokenList tokens);
    AST::StmtPtr ParseRepeatStatement(Lexer::TokenList tokens);
    AST::StmtPtr ParseIfStatement(Lexer::TokenList tokens);
};
