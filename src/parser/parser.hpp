#pragma once

#include <vector>
#include "../error.hpp"
#include "../lexer/st_lexer.hpp"
#include "../ast.hpp"

void Parse(ErrorList &err, Lexer::TokenList tokens);
void ParseFunction(ErrorList &err, Lexer::TokenList tokens);
void ParseFunctionBlock(ErrorList &err, Lexer::TokenList tokens);
void ParseProgram(ErrorList &err, Lexer::TokenList tokens);
void ParseFunctionBlock(ErrorList &err, Lexer::TokenList tokens);
void ParseProgram(ErrorList &err, Lexer::TokenList tokens);
void ParseVarInput(ErrorList &err, Lexer::TokenList tokens);
void ParseVarOutput(ErrorList &err, Lexer::TokenList tokens);
void ParseVarInOut(ErrorList &err, Lexer::TokenList tokens);
void ParseVar(ErrorList &err, Lexer::TokenList tokens);
void ParseVarBody(ErrorList &err, Lexer::TokenList tokens);

void ParseExpression(ErrorList &err, const Lexer::TokenList &tokens);

void SplitNumericLiteral(ErrorList& err, std::string token, std::string *type, std::string *base_str, std::string *number_str);

template <typename T>
void ParseInteger(ErrorList &err, std::string str, int base, T *result);

template <typename T>
void ParseFloat(ErrorList &err, std::string str, int base, T *result);

bool IsInteger(std::string str);

AST::ExprPtr ParseNumericLiteral(ErrorList &err, Lexer::Token token);

// returns true if token is type: `NUMERIC_LITERAL`, `TRUE`, `FALSE`
// in other case returns false
bool IsTokenLiteral(Lexer::TokenType token);

// Scans for specified Tokent Type and returns its position
// Return:
//  -  position in vector if found
//  - `-1` if not found
//
// Example:
// ```
// int pos = FindToken(tokens, Lexer::TokenType::FUNCTION);
// int pos = FindToken(tokens, Lexer::TokenType::FUNCTION_BLOCK);
// int pos = FindToken(tokens, Lexer::TokenType::PROGRAM);
// ```
//
int FindToken(const Lexer::TokenList &tokens, Lexer::TokenType type);

// Scans for specified Tokent Type starting from specified position and returns its position
// Return:
//  -  position in vector if found
//  - `-1` if not found
//
// Example:
// ```
// int pos = FindToken(tokens, 10, Lexer::TokenType::FUNCTION);
// int pos = FindToken(tokens, 10, Lexer::TokenType::FUNCTION_BLOCK);
// int pos = FindToken(tokens, 10, Lexer::TokenType::PROGRAM);
// ```
//
int FindToken(const Lexer::TokenList &tokens, int start_pos, Lexer::TokenType type);

// Scans for specified Tokent Type Pair and returns its position
// Return:
//  - `{first, second}` position in vector if found
//  - `{first, -1}` position in vector if found first but not found second
//  - `{-1,-1}` if pair not found
//
// Example:
// ```
// std::pair<int,int> pos =
//     FindToken(tokens, Lexer::TokenType::FUNCTION, Lexer::TokenType::END_FUNCTION);
// ```
//
std::pair<int, int> FindTokenPair(const Lexer::TokenList &tokens, Lexer::TokenType first, Lexer::TokenType second);

// Scans for specified Tokent Type Pair and returns its position. Start stan from specified pos
// Return:
//  - `{first, second}` position in vector if found
//  - `{first, -1}` position in vector if found first but not found second
//  - `{-1,-1}` if pair not found
//
// Example:
// ```
// std::pair<int,int> pos =
//     FindToken(tokens, Lexer::TokenType::FUNCTION, 10, Lexer::TokenType::END_FUNCTION);
// ```
//
std::pair<int, int> FindTokenPair(const Lexer::TokenList &tokens, int start_pos, Lexer::TokenType first, Lexer::TokenType second);


// Scans for specified connected Tokent Type Pair and returns its position. Start stan from specified pos
// Return:
//  - `{first, second}` position in vector if found
//  - `{first, -1}` position in vector if found first but not found second
//  - `{-1,-1}` if pair not found
//
// Example:
// ```
// std::pair<int,int> pos =
//     FindToken(tokens, Lexer::TokenType::IF, Lexer::TokenType::END_IF);
// ```
//
std::pair<int, int> FindTokenPairWithNeasting(const Lexer::TokenList &tokens, Lexer::TokenType first, Lexer::TokenType second);