#pragma once
#include "error.hpp"
#include "st_lexer.hpp"
#include "ast.hpp"
#include <variant>
#include <list>


typedef std::variant<Lexer::Token, AST::ExprPtr> TokenExprVariant;


std::vector<Error> Parse(const std::vector<Lexer::Token> &tokens);

bool IsTokenType(const TokenExprVariant *token_v, Lexer::TokenType keyword);


bool ParseNumericLiterals(
    TokenExprVariant *token_and_expr,
    std::vector<Error> *err);

bool ParsePOUs(
    std::list<TokenExprVariant> token_and_expr_list,
    std::vector<Error> *err);


