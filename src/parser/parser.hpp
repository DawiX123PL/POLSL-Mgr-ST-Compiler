#pragma once

#include <vector>
#include "../error.hpp"
#include "../lexer/st_lexer.hpp"
#include "../ast.hpp"

AST::POUlist Parse(ErrorList &err, Lexer::TokenList tokens);
AST::POUPtr ParseFunction(ErrorList &err, Lexer::TokenList tokens);
void ParseFunctionBlock(ErrorList &err, Lexer::TokenList tokens);
void ParseProgram(ErrorList &err, Lexer::TokenList tokens);
void ParseFunctionBlock(ErrorList &err, Lexer::TokenList tokens);
void ParseProgram(ErrorList &err, Lexer::TokenList tokens);

std::vector<AST::VariableDeclaration> ParseVarInput(ErrorList &err, Lexer::TokenList tokens);
std::vector<AST::VariableDeclaration> ParseVarOutput(ErrorList &err, Lexer::TokenList tokens);
std::vector<AST::VariableDeclaration> ParseVarInOut(ErrorList &err, Lexer::TokenList tokens);
std::vector<AST::VariableDeclaration> ParseVar(ErrorList &err, Lexer::TokenList tokens);
std::vector<AST::VariableDeclaration> ParseVarBody(ErrorList &err, Lexer::TokenList tokens);

AST::StatementList ParsePOUBody(ErrorList &err, Lexer::TokenList tokens);

AST::StatementPtr ParseStatement(ErrorList &err, const Lexer::TokenList &tokens);

AST::ExprPtr ParseExpression(ErrorList &err, const Lexer::TokenList &tokens);

AST::ExprPtr ParseVariable(ErrorList &err, Lexer::Token token);

void SplitNumericLiteral(
    ErrorList &err,
    std::string token,
    std::string *type,
    std::string *base_str,
    std::string *number_str,
    bool *has_type,
    bool *has_base);

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

// Check if index is in bounds of container
// Returns:
//  - `true` if valid index
//  - `false` if out of bounds
//
// Example:
// ```
// if(IsIndexInBounds(tokens, index)){
//     ...
// }
// ```
//
template <typename T_vec>
bool IsIndexInBounds(T_vec vec, int index);

// Checks if specified token is in vector at specified index (with bound checking)
// Returns:
//  - `true` if valid index and token on index has specified type
//  - `false` if out of bounds
//
// Example:
// ```
// if(!IsTokenInPosition(tokens, 0, Lexer::TokenType::FUNCTION)){
//     // ERROR: Expected FUNCTION keyword
// }
// ```
//
bool IsTokenInPosition(const Lexer::TokenList &tokens, int index, Lexer::TokenType type);
