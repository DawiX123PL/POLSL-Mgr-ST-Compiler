#include "st_expression_parser.hpp"

// recursive descend parser
// - LL(1)
namespace StParser::Expression
{

    

    AST::ExprPtr Parse(Error::ErrorList_t &err, Lexer::TokenList tokens)
    {
        RecursiveDescendParser parser;
        parser.AssignError(&err);

        return parser.Parse(tokens);
    }

}