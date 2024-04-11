#include "parser.hpp"
#include <tuple>
#include <utility>
#include <cassert>
#include <variant>
#include <list>
#include "../ast.hpp"
#include <charconv>
#include <inttypes.h>

Lexer::TokenList SubVector(const Lexer::TokenList &tokens, std::pair<int, int> pair_pos)
{
    return Lexer::TokenList{&tokens[pair_pos.first], &tokens[pair_pos.second] + 1};
}

Lexer::TokenList SubVector(const Lexer::TokenList &tokens, int first, int last)
{
    return Lexer::TokenList{&tokens[first], &tokens[last] + 1};
}

void Parse(ErrorList &err, Lexer::TokenList tokens)
{
    if (tokens.size() == 0)
    {
        return;
    }

    // Scan for blocks in current position:
    //  - "FUNCTION"
    //  - "FUNCTION_BLOCK"
    //  - "PROGRAM"

    int current_pos = 0;

    while (current_pos < tokens.size())
    {

        {
            std::pair<int, int> pair_pos = FindTokenPair(tokens, current_pos, Lexer::TokenType::FUNCTION, Lexer::TokenType::END_FUNCTION);
            if (pair_pos.second == -1)
            {
                err.emplace_back("Missing END_FUNCTION at the end of FUNCTION ");
                return;
            }

            if (pair_pos.second >= 0)
            {
                ParseFunction(err, SubVector(tokens, pair_pos));
                current_pos = pair_pos.second + 1;
                continue;
            }
        }

        {
            std::pair<int, int> pair_pos = FindTokenPair(tokens, current_pos, Lexer::TokenType::FUNCTION_BLOCK, Lexer::TokenType::END_FUNCTION_BLOCK);
            if (pair_pos.second == -1)
            {
                err.emplace_back("Missing END_FUNCTION_BLOCK at the end of FUNCTION_BLOCK ");
                return;
            }

            if (pair_pos.second >= 0)
            {
                ParseFunctionBlock(err, SubVector(tokens, pair_pos));
                current_pos = pair_pos.second + 1;
                continue;
            }
        }

        {
            std::pair<int, int> pair_pos = FindTokenPair(tokens, current_pos, Lexer::TokenType::PROGRAM, Lexer::TokenType::END_PROGRAM);
            if (pair_pos.second == -1)
            {
                err.emplace_back("Missing END_PROGRAM at the end of PROGRAM ");
                return;
            }

            if (pair_pos.second >= 0)
            {
                ParseProgram(err, SubVector(tokens, pair_pos));
                current_pos = pair_pos.second + 1;
                continue;
            }
        }

        err.emplace_back("Unexpected token");
        return;
    }

    return;
}

void ParseFunction(ErrorList &err, Lexer::TokenList tokens)
{

    if (tokens.size() == 0)
    {
        err.emplace_back("Internal Error - Expected non-empty vector of tokens");
        return;
    }

    // first few tokens should be:
    // FUNCTION function_name : return_type

    // FUNTION
    if (tokens.size() < 1)
    {
        err.emplace_back("Missing FUNCTION keyword");
        return;
    }

    if (tokens[0].type != Lexer::TokenType::FUNCTION)
    {
        err.emplace_back("Expected FUNCTION keyword");
        return;
    }

    // function_name
    if (tokens.size() < 2)
    {
        err.emplace_back("Missing Function name");
        return;
    }

    if (tokens[1].type != Lexer::TokenType::IDENTIFIER)
    {
        err.emplace_back("Expected identifier (specifying function name)");
        return;
    }

    // :
    if (tokens.size() < 3)
    {
        err.emplace_back("Missing COLON");
        return;
    }

    if (tokens[2].type != Lexer::TokenType::COLON)
    {
        err.emplace_back("Expected COLON");
        return;
    }

    // return_type
    if (tokens.size() < 4)
    {
        err.emplace_back("Missing Data Type");
        return;
    }

    if (tokens[3].type != Lexer::TokenType::IDENTIFIER)
    {
        err.emplace_back("Expected Identifier (specifying return type)");
        return;
    }

    // last token should be END_FUNCTION
    if (tokens.back().type != Lexer::TokenType::END_FUNCTION)
    {
        err.emplace_back("Expected END_FUNCTION");
        return;
    }

    //

    std::string function_name = tokens[1].str;
    std::string return_type = tokens[3].str;

    // scan for block:
    //  - VAR_INPUT
    //  - VAR_OUTPUT
    //  - VAR_IN_OUT
    //  - VAR

    int current_pos = 4;
    while (current_pos < tokens.size())
    {

        { // VAR_INPUT
            std::pair<int, int> pair_pos = FindTokenPair(tokens, current_pos, Lexer::TokenType::VAR_INPUT, Lexer::TokenType::END_VAR);
            if (pair_pos.first >= 0 && pair_pos.second == -1)
            {
                err.emplace_back("Missing END_FUNCTION at the end of FUNCTION ");
                return;
            }

            if (pair_pos.first >= 0 && pair_pos.second >= 0)
            {
                ParseVarInput(err, SubVector(tokens, pair_pos));
                current_pos = pair_pos.second + 1;
                continue;
            }
        }

        { // VAR_OUTPUT
            std::pair<int, int> pair_pos = FindTokenPair(tokens, current_pos, Lexer::TokenType::VAR_OUTPUT, Lexer::TokenType::END_VAR);
            if (pair_pos.first >= 0 && pair_pos.second == -1)
            {
                err.emplace_back("Missing END_FUNCTION at the end of FUNCTION ");
                return;
            }

            if (pair_pos.first >= 0 && pair_pos.second >= 0)
            {
                ParseVarOutput(err, SubVector(tokens, pair_pos));
                current_pos = pair_pos.second + 1;
                continue;
            }
        }
        { // VAR_IN_OUT
            std::pair<int, int> pair_pos = FindTokenPair(tokens, current_pos, Lexer::TokenType::VAR_IN_OUT, Lexer::TokenType::END_VAR);
            if (pair_pos.first >= 0 && pair_pos.second == -1)
            {
                err.emplace_back("Missing END_FUNCTION at the end of FUNCTION ");
                return;
            }

            if (pair_pos.first >= 0 && pair_pos.second >= 0)
            {
                ParseVarInOut(err, SubVector(tokens, pair_pos));
                current_pos = pair_pos.second + 1;
                continue;
            }
        }
        { // VAR
            std::pair<int, int> pair_pos = FindTokenPair(tokens, current_pos, Lexer::TokenType::VAR, Lexer::TokenType::END_VAR);
            if (pair_pos.first >= 0 && pair_pos.second == -1)
            {
                err.emplace_back("Missing END_FUNCTION at the end of FUNCTION ");
                return;
            }

            if (pair_pos.first >= 0 && pair_pos.second >= 0)
            {
                ParseVar(err, SubVector(tokens, pair_pos));
                current_pos = pair_pos.second + 1;
                continue;
            }
        }

        break;
    }

    Lexer::TokenList function_body = SubVector(tokens, current_pos, tokens.size() - 1);
}

void ParseFunctionBlock(ErrorList &err, Lexer::TokenList tokens)
{
    err.emplace_back("Parsing Function Block not yet implemented");
    return;
}

void ParseProgram(ErrorList &err, Lexer::TokenList tokens)
{
    err.emplace_back("Parsing Program not yet implemented");
    return;
}

///////////////////////////

void ParseVarInput(ErrorList &err, Lexer::TokenList tokens)
{
    if (tokens.size() == 0)
    {
        return;
    }

    // First token must be VAR_INPUT
    if (tokens.size() < 1)
    {
        err.emplace_back("Missing VAR_INPUT keyword");
        return;
    }

    if (tokens[0].type != Lexer::TokenType::VAR_INPUT)
    {
        err.emplace_back("Expected VAR_INPUT keyword");
        return;
    }

    // last token must be END_VAR
    if (tokens.back().type != Lexer::TokenType::END_VAR)
    {
        err.emplace_back("Expected END_VAR keyword");
        return;
    }

    // parse block body
    ParseVarBody(err, SubVector(tokens, 1, tokens.size() - 2));
}

void ParseVarOutput(ErrorList &err, Lexer::TokenList tokens)
{
    if (tokens.size() == 0)
    {
        return;
    }

    // First token must be VAR_OUTPUT
    if (tokens.size() < 1)
    {
        err.emplace_back("Missing VAR_OUTPUT keyword");
        return;
    }

    if (tokens[0].type != Lexer::TokenType::VAR_OUTPUT)
    {
        err.emplace_back("Expected VAR_OUTPUT keyword");
        return;
    }

    // last token must be END_VAR
    if (tokens.back().type != Lexer::TokenType::END_VAR)
    {
        err.emplace_back("Expected END_VAR keyword");
        return;
    }

    // parse block body
    ParseVarBody(err, SubVector(tokens, 1, tokens.size() - 2));

    return;
}

void ParseVarInOut(ErrorList &err, Lexer::TokenList tokens)
{
    if (tokens.size() == 0)
    {
        return;
    }

    // First token must be VAR_IN_OUT
    if (tokens.size() < 1)
    {
        err.emplace_back("Missing VAR_IN_OUT keyword");
        return;
    }

    if (tokens[0].type != Lexer::TokenType::VAR_IN_OUT)
    {
        err.emplace_back("Expected VAR_IN_OUT keyword");
        return;
    }

    // last token must be END_VAR
    if (tokens.back().type != Lexer::TokenType::END_VAR)
    {
        err.emplace_back("Expected END_VAR keyword");
        return;
    }

    // parse block body
    ParseVarBody(err, SubVector(tokens, 1, tokens.size() - 2));

    return;
}

void ParseVar(ErrorList &err, Lexer::TokenList tokens)
{
    if (tokens.size() == 0)
    {
        return;
    }

    // First token must be VAR
    if (tokens.size() < 1)
    {
        err.emplace_back("Missing VAR keyword");
        return;
    }

    if (tokens[0].type != Lexer::TokenType::VAR)
    {
        err.emplace_back("Expected VAR keyword");
        return;
    }

    // last token must be END_VAR
    if (tokens.back().type != Lexer::TokenType::END_VAR)
    {
        err.emplace_back("Expected END_VAR keyword");
        return;
    }

    // parse block body
    ParseVarBody(err, SubVector(tokens, 1, tokens.size() - 2));
}

///////////////////////////

void ParseVarBody(ErrorList &err, Lexer::TokenList tokens)
{
    // name : data_type;
    // name : datatype := expr;

    err.emplace_back("Parsing Var not yet implemented");
}

/////////////////////////////////

// TODO
void ParseStatement(ErrorList &err, const Lexer::TokenList &tokens)
{
    // check for IF statement
    // check for WHILE statement
    // check for assignment statement
}

/////////////////////////////////

struct OperatorType
{
    enum class Type
    {
        INFIX,
        PREFIX,
        SUFIX,
    };

    Type type;
    Lexer::TokenType token;
    int priority;

    OperatorType(Type _type, Lexer::TokenType _token, int _priority) : type(_type),
                                                                       token(_token),
                                                                       priority(_priority) {}
};

OperatorType OperatorTypeList[] = {

    {OperatorType::Type::SUFIX, Lexer::TokenType::DEREFERENCE, 9},      // ex "^"
    {OperatorType::Type::PREFIX, Lexer::TokenType::MINUS, 8},           // "-" ex
    {OperatorType::Type::PREFIX, Lexer::TokenType::PLUS, 8},            // "+" ex
    {OperatorType::Type::PREFIX, Lexer::TokenType::NEGATION, 8},        // ex "NOT"
    {OperatorType::Type::INFIX, Lexer::TokenType::EXPONENTIATION, 7},   // ex "**" ex
    {OperatorType::Type::INFIX, Lexer::TokenType::MULTIPLY, 6},         // ex "*" ex
    {OperatorType::Type::INFIX, Lexer::TokenType::DIVIDE, 6},           // ex "/" ex
    {OperatorType::Type::INFIX, Lexer::TokenType::MODULO, 6},           // ex "mod" ex
    {OperatorType::Type::INFIX, Lexer::TokenType::PLUS, 5},             // ex "+" ex
    {OperatorType::Type::INFIX, Lexer::TokenType::MINUS, 5},            // ex "-" ex
    {OperatorType::Type::INFIX, Lexer::TokenType::GREATER_THAN, 4},     // ex ">" ex
    {OperatorType::Type::INFIX, Lexer::TokenType::LESS_THAN, 4},        // ex "<" ex
    {OperatorType::Type::INFIX, Lexer::TokenType::GREATER_OR_EQUAL, 4}, // ex ">=" ex
    {OperatorType::Type::INFIX, Lexer::TokenType::LESS_OR_EQUAL, 4},    // ex "<=" ex
    {OperatorType::Type::INFIX, Lexer::TokenType::EQUALITY, 4},         // ex "=" ex
    {OperatorType::Type::INFIX, Lexer::TokenType::INEQUALITY, 4},       // ex "<>" ex
    {OperatorType::Type::INFIX, Lexer::TokenType::BOOLEAN_AND, 3},      // ex "AND" ex | // ex "&" ex
    {OperatorType::Type::INFIX, Lexer::TokenType::BOOLEAN_XOR, 2},      // ex "XOR" ex
    {OperatorType::Type::INFIX, Lexer::TokenType::BOOLEAN_OR, 1}        // ex "OR" ex

};

void ParseExpression(ErrorList &err, const Lexer::TokenList &tokens)
{
    // step 1 copy to variant table
    std::vector<std::variant<Lexer::Token, AST::ExprPtr>> token_expr_vec;
    for (int i = 0; i < tokens.size(); i++)
    {
        if (IsTokenLiteral(tokens[i].type))
        {
            // step 1.1 parse literals
            AST::ExprPtr literal = ParseNumericLiteral(err, tokens[i]);
            token_expr_vec.push_back(literal);
        }
        else
        {
            token_expr_vec.push_back(tokens[i]);
        }
    }

    // step 3 parse operators
    for (int precedence = 11; precedence > 0; precedence--)
    {
        // TODO:
    }
}

void SplitNumericLiteral(ErrorList &err, std::string token, std::string *type, std::string *base_str, std::string *number_str)
{
    // step 0 split to parts if number has hashes
    int first_hash = token.find('#');
    int second_hash = token.find('#', first_hash + 1);

    if (first_hash == 0)
    {
        err.emplace_back("error: \"#\" cannot be first element \n");
        return;
    }

    if (first_hash >= 0 && second_hash >= 0)
    {
        // type "#" base "#" number
        // step 1 - determine type and base of number
        *type = token.substr(0, first_hash);
        *base_str = token.substr(first_hash + 1, second_hash - first_hash - 1);
        *number_str = token.substr(second_hash + 1);
        return;
    }

    else if (first_hash >= 0 && second_hash < 0)
    {
        // base "#" number
        // type "#" number
        // step 1 - determine type and base of number
        std::string base_or_type_str = token.substr(0, first_hash);

        if (std::isdigit(base_or_type_str[0]))
        {
            *type = "";
            *base_str = token.substr(0, first_hash);
            *number_str = token.substr(first_hash + 1);
            return;
        }
        else
        {
            *type = token.substr(0, first_hash);
            *base_str = "";
            *number_str = token.substr(first_hash + 1);
            return;
        }
    }

    else if (first_hash < 0 && second_hash < 0)
    {
        // number must be REAL or INT base 10
        *type = "";
        *base_str = "";
        *number_str = token;
        return;
    }

    // TODO: error case
}

template <typename T>
void ParseInteger(ErrorList &err, std::string str, int base, T *result)
{
    T number;
    std::from_chars_result conversion_result = std::from_chars(str.c_str(), str.c_str() + str.size(), number, base);
    *result = number;

    // not all characters consumed
    if (conversion_result.ptr != str.c_str() + str.size())
    {
        err.push_back("error: \"" + str + "\" is not valid base " + std::to_string(base) + " number. \n");
        return;
    }

    // other error
    if (conversion_result.ec != std::errc())
    {
        ;

        err.push_back("error: \"" + str + "\" is not valid base " + std::to_string(base) + " number. \n");
        return;
    }
}

template <typename T>
void ParseFloat(ErrorList &err, std::string str, int base, T *result)
{
    T number;
    std::from_chars_result conversion_result = std::from_chars(str.c_str(), str.c_str() + str.size(), number, std::chars_format::general);
    *result = number;

    // not all characters consumed
    if (conversion_result.ptr != str.c_str() + str.size())
    {
        err.push_back("error: \"" + str + "\" is not valid base " + std::to_string(base) + " number. \n");
        return;
    }

    // other error
    if (conversion_result.ec != std::errc())
    {
        err.push_back("error: \"" + str + "\" is not valid base " + std::to_string(base) + " number. \n");
        return;
    }
}

bool IsInteger(std::string str)
{
    // must not contain dot
    for (int i = 0; i < str.size(); i++)
    {
        char c = str[i];
        if (c == '.')
        {
            return false;
        }
    }
    return true;
}

// TODO: finish this function
AST::ExprPtr ParseNumericLiteral(ErrorList &err, Lexer::Token token)
{
    std::string type;
    std::string base_str;
    std::string number_str;
    SplitNumericLiteral(err, token.str, &type, &base_str, &number_str);

    int64_t base = 0;
    ParseInteger<int64_t>(err, base_str, 10, &base);

    if (base < 2 || base > 36)
    {
        err.emplace_back("Error : base must be in range [2, 36]");
        return AST::LiteralSpecific::Create_INT(0);
    }

    // ambiguous type
    if (type == "")
    {

        err.emplace_back("Error : Literals of unspecified type are not implemented");
        return AST::LiteralSpecific::Create_INT(0);
        // if (IsInteger(number_str))
        // {
        //     int64_t value = 0;
        //     ParseInteger<int64_t>(err, number_str, base, &value);
        //     return Literal(value);
        // }
        // else
        // {
        //     double value = 0;
        //     ParseFloat<double>(err, number_str, base, &value);
        //     return Literal(value);
        // }
    }

    // specific type
    if (type == "BOOL")
    {
        if (number_str == "FALSE")
        {
            return AST::LiteralSpecific::Create_BOOL(false);
        }
        else if (number_str == "TRUE")
        {
            return AST::LiteralSpecific::Create_BOOL(true);
        }
        else
        {
            int64_t value = 0;
            ParseInteger<int64_t>(err, number_str, base, &value);

            if (value == 0)
            {
                return AST::LiteralSpecific::Create_BOOL(false);
            }
            if (value == 1)
            {
                return AST::LiteralSpecific::Create_BOOL(true);
            }

            err.emplace_back("Error: BOOL value must be 0 or 1");
            return AST::LiteralSpecific::Create_BOOL(false);
        }
    }

    if (type == "SINT") // int8_t
    {
        int8_t value = 0;
        ParseInteger<int8_t>(err, number_str, base, &value);
        return AST::LiteralSpecific::Create_SINT(value);
    }
    if (type == "INT") // int16_t
    {
        int16_t value = 0;
        ParseInteger<int16_t>(err, number_str, base, &value);
        return AST::LiteralSpecific::Create_INT(value);
    }
    if (type == "DINT") // int32_t
    {
        int32_t value = 0;
        ParseInteger<int32_t>(err, number_str, base, &value);
        return AST::LiteralSpecific::Create_DINT(value);
    }
    if (type == "LINT") // int64_t
    {
        int64_t value = 0;
        ParseInteger<int64_t>(err, number_str, base, &value);
        return AST::LiteralSpecific::Create_LINT(value);
    }
    if (type == "USINT") // uint8_t
    {
        uint8_t value = 0;
        ParseInteger<uint8_t>(err, number_str, base, &value);
        return AST::LiteralSpecific::Create_USINT(value);
    }
    if (type == "UINT") // uint16_t
    {
        uint16_t value = 0;
        ParseInteger<uint16_t>(err, number_str, base, &value);
        return AST::LiteralSpecific::Create_UINT(value);
    }
    if (type == "UDINT") // uint32_t
    {
        uint32_t value = 0;
        ParseInteger<uint32_t>(err, number_str, base, &value);
        return AST::LiteralSpecific::Create_UDINT(value);
    }
    if (type == "ULINT") // uint64_t
    {
        uint64_t value = 0;
        ParseInteger<uint64_t>(err, number_str, base, &value);
        return AST::LiteralSpecific::Create_ULINT(value);
    }
    if (type == "REAL") // float
    {
        float value = 0;
        ParseFloat<float>(err, number_str, base, &value);
        return AST::LiteralSpecific::Create_REAL(value);
    }
    if (type == "LREAL") // double
    {
        double value = 0;
        ParseFloat<double>(err, number_str, base, &value);
        return AST::LiteralSpecific::Create_LREAL(value);
    }

    // error case
    err.emplace_back("Error: \"" + type + "\" is not valid type");
    return AST::LiteralSpecific::Create_INT(0);
}

bool IsTokenLiteral(Lexer::TokenType token)
{
    return (token == Lexer::TokenType::NUMERIC_LITERAL) ||
           (token == Lexer::TokenType::FALSE) ||
           (token == Lexer::TokenType::TRUE);
}

int FindToken(const Lexer::TokenList &tokens, int start_pos, Lexer::TokenType type)
{
    for (int i = start_pos; i < tokens.size(); i++)
    {
        if (tokens[i].type == type)
        {
            return i;
        }
    }
    return -1;
}

int FindToken(const Lexer::TokenList &tokens, Lexer::TokenType type)
{
    return FindToken(tokens, 0, type);
}

std::pair<int, int> FindTokenPair(const Lexer::TokenList &tokens, int start_pos, Lexer::TokenType first, Lexer::TokenType second)
{

    int first_pos = -1;
    int second_pos = -1;

    // scan for first token
    first_pos = FindToken(tokens, start_pos, first);

    // scan for second token
    second_pos = FindToken(tokens, first_pos, second);

    return {first_pos, second_pos};
}

std::pair<int, int> FindTokenPair(const Lexer::TokenList &tokens, Lexer::TokenType first, Lexer::TokenType second)
{
    return FindTokenPair(tokens, 0, first, second);
}

// TODO: check if this function works correctly
std::pair<int, int> FindTokenPairWithNeasting(const Lexer::TokenList &tokens, Lexer::TokenType first, Lexer::TokenType second)
{
    int counter = 0;
    int first_pos = -1;
    int second_pos = -1;

    int begin = FindToken(tokens, first);

    if (begin == -1)
    {
        return {-1, -1};
    }

    for (int i = begin; i < tokens.size(); i++)
    {
        if (tokens[i].type == first)
        {
            if (counter == 0)
            {
                first_pos = i;
            }
            counter++;
        }
        else if (tokens[i].type == second)
        {
            counter--;
            if (counter == 0)
            {
                second_pos = i;
                return {first_pos, second_pos};
            }
        }
    }

    return {first_pos, second_pos};
}
