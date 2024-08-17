#include "st_expression_parser.hpp"

// recursive descend parser
// - LL(1)
namespace StParser::Expression
{

    

    AST::ExprPtr Parse(Error::ErrorList_t &err, Lexer::TokenList tokens)
    {
        RecursiveDescendParser parser;
        parser.AssignError(&err);

        // FIXME: this function might return even if not all tokens were consumed
        return parser.Parse(tokens);
    }

}