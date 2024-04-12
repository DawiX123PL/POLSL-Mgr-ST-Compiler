#pragma once

#include "../error.hpp"
#include "../lexer/st_lexer.hpp"
#include "../ast.hpp"
#include <variant>
#include <list>

class TokenExprVariant
{
    bool is_token;
    Lexer::Token token;
    AST::ExprPtr expr;

public:
    TokenExprVariant(Lexer::Token _token) : token(_token), expr(nullptr), is_token(true) {}
    TokenExprVariant(AST::ExprPtr _expr) : token(), expr(_expr), is_token(false) {}

    Lexer::Token *GetToken()
    {
        if (is_token)
            return &token;
        else
            return nullptr;
    }

    AST::ExprPtr GetExpr()
    {
        if (!is_token)
            return expr;
        else
            return nullptr;
    }

    void operator=(Lexer::Token _token)
    {
        token = _token;
        expr = nullptr;
        is_token = true;
    }

    void operator=(AST::ExprPtr _expr)
    {
        token = Lexer::Token();
        expr = _expr;
        is_token = false;
    }
};

bool ParseStatementList(std::vector<Error> *err, std::vector<Lexer::Token> tokens, AST::StatementList* stmt_list);

std::vector<Lexer::Token> FindIfStatementRange(const std::vector<Lexer::Token> &tokens, int begin);

bool ParseIfStatement(std::vector<Error> *err, const std::vector<Lexer::Token> &tokens, int begin_index, int *next_stmt_index);

bool ParseSimpleStatement(std::vector<Error> *err, const std::vector<Lexer::Token> &tokens, int begin_index, int *next_stmt_index, AST::StatementPtr* stmt_ptr);

bool ParseExpression(std::vector<Error> *err, const std::vector<Lexer::Token> &tokens, AST::ExprPtr* expr);

bool ParseVariableExpr(std::vector<Error> *err, std::list<TokenExprVariant> *token_variant_list);

bool ParseNumericLiteral(std::vector<Error> *err, TokenExprVariant *token_and_expr);

bool ParseExprLiterals(std::vector<Error> *err, std::list<TokenExprVariant> *token_variant_list);

bool GetBinaryExprOperator(
    std::vector<Error> *err,
    std::list<TokenExprVariant> *tokens,
    std::list<TokenExprVariant>::iterator begin,
    Lexer::TokenType *_operator,
    AST::ExprPtr *expression1,
    AST::ExprPtr *expression2);

bool ParseOperatorsWithPriority(std::vector<Error> *err, int current_priority, std::list<TokenExprVariant> *token_variant_list);
