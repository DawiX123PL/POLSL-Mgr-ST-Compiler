#pragma once
#include "error.hpp"
#include "st_lexer.hpp"
#include "ast.hpp"
#include "st_expression_parser.hpp"
#include <variant>
#include <list>



std::vector<Error> Parse(const std::vector<Lexer::Token> &tokens);

// bool ParseNumericLiterals(
//     std::vector<Error> *err,
//     TokenExprVariant *token_and_expr);

bool ParseFunction(std::vector<Error> *err, const std::vector<Lexer::Token> &tokens);

std::vector<AST::VariableDefinition> ParseVarList(
    std::vector<Error> *err,
    const std::vector<Lexer::Token>& tokens);

bool ParseVarDeclaration(
    std::vector<Error> *err,
    const std::vector<Lexer::Token>& tokens,
    AST::VariableDefinition *variable);

int FindKeyword(
    const std::vector<Lexer::Token> &tokens,
    int begin,
    Lexer::TokenType keyword);

int FindKeyword(
    const std::vector<Lexer::Token> &tokens,
    Lexer::TokenType keyword);
