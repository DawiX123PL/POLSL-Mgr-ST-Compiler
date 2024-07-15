#pragma once

#include <utility>
#include "../error.hpp"
#include "../lexer/st_lexer.hpp"
#include "../ast/ast.hpp"

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
    bool ExpectToken(Error::ErrorList_t &err, const Lexer::TokenList &tokens, int index, Lexer::TokenType type);

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
    // parsing functions

    // Parses whole file content
    void Parse(Error::ErrorList_t &err, Lexer::TokenList tokens);

    void ParseFunction(Error::ErrorList_t &err, Lexer::TokenList tokens);
    void ParseFunctionBlock(Error::ErrorList_t &err, Lexer::TokenList tokens);
    void ParseProgram(Error::ErrorList_t &err, Lexer::TokenList tokens);

    void ParsePouBody(Error::ErrorList_t &err, Lexer::TokenList tokens);
    void ParseVarBody(Error::ErrorList_t &err, Lexer::TokenList tokens);

    void ParseAllVars(Error::ErrorList_t &err, Lexer::TokenList tokens, int *last_position);
    void ParseVar(Error::ErrorList_t &err, Lexer::TokenList tokens);
    void ParseVarInput(Error::ErrorList_t &err, Lexer::TokenList tokens);
    void ParseVarInOut(Error::ErrorList_t &err, Lexer::TokenList tokens);
    void ParseVarOutput(Error::ErrorList_t &err, Lexer::TokenList tokens);
    void ParseVariableDeclaration(Error::ErrorList_t &err, Lexer::TokenList tokens);

    void ParseStatementList(Error::ErrorList_t &err, Lexer::TokenList tokens);
    void ParseIfStatement(Error::ErrorList_t &err, Lexer::TokenList tokens);


};
