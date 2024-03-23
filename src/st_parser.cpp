#include "ast.hpp"
#include "st_parser.hpp"
#include "st_lexer.hpp"
#include <variant>
#include <vector>
#include <list>
#include <charconv>

std::vector<Error> Parse(const std::vector<Lexer::Token> &tokens)
{

    std::list<
        std::variant<
            Lexer::Token,
            AST::ExprPtr>>
        token_and_expr_list;

    std::vector<Error> err;

    // construct token and expr list
    for (int i = 0; i < tokens.size(); i++)
    {
        token_and_expr_list.emplace_back(tokens[i]);
    }

    // 1. Parse numeric literals
    for (auto iter = token_and_expr_list.begin(); iter != token_and_expr_list.end(); iter++)
    {
        TokenExprVariant *token_expr = &(*iter);
        ParseNumericLiterals(token_expr, &err);
    }

    // 2. Parse POUs definitions
    

    return err;
}

bool ParseNumericLiterals(
    TokenExprVariant *token_and_expr,
    std::vector<Error> *err)
{
    if (token_and_expr == nullptr)
    {
        err->emplace_back(Error::ErrorType::UNNOWN,
                          "Internal compiler error - this is caused because creator of this compiler is a moron.");
        return false;
    }

    Lexer::Token *token = std::get_if<Lexer::Token>(token_and_expr);

    if (token == nullptr)
    {
        return false;
    }

    if (token->type != Lexer::TokenType::NUMERIC_LITERAL)
    {
        return false;
    }

    // try performing conversion
    const char *first = token->str.c_str();
    const char *last = first + token->str.size();

    bool is_float = 0;
    // check if floating point

    for (int i = 0; i < token->str.size(); i++)
    {
        char c = token->str[i];

        is_float = (c == '.') || (c == 'E') || (c == 'e');
        if (is_float)
        {
            break;
        }
    }

    if (is_float)

    { // try conversion to double
        double number = 0;
        std::from_chars_result result = std::from_chars(first, last, number);
        if (result.ec == std::errc())
        {
            *token_and_expr = std::make_unique<AST::Literal>(AST::Literal(number));
            return true;
        }
    }

    else

    { // try conversion to integer
        int64_t number = 0;
        std::from_chars_result result = std::from_chars(first, last, number);
        if (result.ec == std::errc())
        {

            *token_and_expr = std::make_unique<AST::Literal>(AST::Literal(number));
            return true;
        }
    }

    err->emplace_back(Error::ErrorType::UNNOWN,
                      "Cannot parse numeric literal + " + token->str + " + at position: " + token->pos.ToString());
    return false;
}


bool IsTokenType(const TokenExprVariant *token_v, Lexer::TokenType keyword)
{
    const Lexer::Token *token = std::get_if<Lexer::Token>(token_v);

    if (token == nullptr)
    {
        return false;
    }

    return token->type == keyword;
}

