#include "parser.hpp"
#include <tuple>
#include <utility>
#include <cassert>
#include <variant>
#include <list>
#include "../ast/ast.hpp"
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

AST::POUlist Parse(ErrorList_t &err, Lexer::TokenList tokens)
{
    if (tokens.size() == 0)
    {
        return {};
    }

    AST::POUlist pou_list;

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
                return pou_list;
            }

            if (pair_pos.second >= 0)
            {
                AST::POUPtr fn = ParseFunction(err, SubVector(tokens, pair_pos));
                pou_list.push_back(fn);
                current_pos = pair_pos.second + 1;
                continue;
            }
        }

        {
            std::pair<int, int> pair_pos = FindTokenPair(tokens, current_pos, Lexer::TokenType::FUNCTION_BLOCK, Lexer::TokenType::END_FUNCTION_BLOCK);
            if (pair_pos.second == -1)
            {
                err.emplace_back("Missing END_FUNCTION_BLOCK at the end of FUNCTION_BLOCK ");
                return pou_list;
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
                return pou_list;
            }

            if (pair_pos.second >= 0)
            {
                ParseProgram(err, SubVector(tokens, pair_pos));
                current_pos = pair_pos.second + 1;
                continue;
            }
        }

        err.emplace_back("Unexpected token");
        return pou_list;
    }

    return pou_list;
}

AST::POUPtr ParseFunction(ErrorList_t &err, Lexer::TokenList tokens)
{

    if (tokens.size() == 0)
    {
        err.emplace_back("Internal Error - Expected non-empty vector of tokens");
        return nullptr;
    }

    // first few tokens should be:
    // FUNCTION function_name : return_type

    // FUNTION
    if (!IsTokenInPosition(tokens, 0, Lexer::TokenType::FUNCTION))
    {
        err.emplace_back("Expected FUNCTION keyword");
        return nullptr;
    }

    // function_name
    if (!IsTokenInPosition(tokens, 1, Lexer::TokenType::IDENTIFIER))
    {
        err.emplace_back("Expected identifier (specifying function name)");
        return nullptr;
    }

    // :
    if (!IsTokenInPosition(tokens, 2, Lexer::TokenType::COLON))
    {
        err.emplace_back("Expected COLON");
        return nullptr;
    }

    // return_type
    if (!IsTokenInPosition(tokens, 3, Lexer::TokenType::IDENTIFIER))
    {
        err.emplace_back("Expected Identifier (specifying return type)");
        return nullptr;
    }

    // last token should be END_FUNCTION
    if (tokens.back().type != Lexer::TokenType::END_FUNCTION)
    {
        err.emplace_back("Expected END_FUNCTION");
        return nullptr;
    }

    //
    AST::Function function;
    function.name = tokens[1].str;

    AST::DataType type = AST::StringToDataType(tokens[3].str);
    if(type == AST::DataType::UNNOWN){
        err.emplace_back("\'" + tokens[3].str + "\' is not valud data type");
    }

    function.var_return = AST::VariableDeclaration(tokens[1].str, type);

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
            if (pair_pos.first == current_pos && pair_pos.second == -1)
            {
                err.emplace_back("Missing END_VAR at the end of VAR_INPUT ");
                return AST::Function::Make(function);
            }

            if (pair_pos.first == current_pos && pair_pos.second >= 0)
            {
                function.var_input = ParseVarInput(err, SubVector(tokens, pair_pos));
                current_pos = pair_pos.second + 1;
                continue;
            }
        }

        { // VAR_OUTPUT
            std::pair<int, int> pair_pos = FindTokenPair(tokens, current_pos, Lexer::TokenType::VAR_OUTPUT, Lexer::TokenType::END_VAR);
            if (pair_pos.first == current_pos && pair_pos.second == -1)
            {
                err.emplace_back("Missing END_VAR at the end of VAR_OUTPUT ");
                return AST::Function::Make(function);
            }

            if (pair_pos.first == current_pos && pair_pos.second >= 0)
            {
                function.var_output = ParseVarOutput(err, SubVector(tokens, pair_pos));
                current_pos = pair_pos.second + 1;
                continue;
            }
        }
        { // VAR_IN_OUT
            std::pair<int, int> pair_pos = FindTokenPair(tokens, current_pos, Lexer::TokenType::VAR_IN_OUT, Lexer::TokenType::END_VAR);
            if (pair_pos.first == current_pos && pair_pos.second == -1)
            {
                err.emplace_back("Missing END_VAR at the end of VAR_IN_OUT ");
                return AST::Function::Make(function);
            }

            if (pair_pos.first == current_pos && pair_pos.second >= 0)
            {
                function.var_in_out = ParseVarInOut(err, SubVector(tokens, pair_pos));
                current_pos = pair_pos.second + 1;
                continue;
            }
        }
        { // VAR
            std::pair<int, int> pair_pos = FindTokenPair(tokens, current_pos, Lexer::TokenType::VAR, Lexer::TokenType::END_VAR);
            if (pair_pos.first == current_pos && pair_pos.second == -1)
            {
                err.emplace_back("Missing END_VAR at the end of END_VAR ");
                return AST::Function::Make(function);
            }

            if (pair_pos.first == current_pos && pair_pos.second >= 0)
            {
                function.var_temp = ParseVar(err, SubVector(tokens, pair_pos));
                current_pos = pair_pos.second + 1;
                continue;
            }
        }

        break;
    }

    Lexer::TokenList function_body = SubVector(tokens, current_pos, tokens.size() - 2);
    AST::StatementList statement_list = ParsePOUBody(err, function_body);

    function.statement_list = statement_list;

    return AST::Function::Make(function);
}

void ParseFunctionBlock(ErrorList_t &err, Lexer::TokenList tokens)
{
    err.emplace_back("Parsing Function Block not yet implemented");
    return;
}

void ParseProgram(ErrorList_t &err, Lexer::TokenList tokens)
{
    err.emplace_back("Parsing Program not yet implemented");
    return;
}

///////////////////////////

// TODO: parse IF, SWITCH and loops. for now this function threads all statemens as:
// - assignment statement
// - empty statement
AST::StatementList ParsePOUBody(ErrorList_t &err, Lexer::TokenList tokens)
{
    AST::StatementList statement_list;

    int statement_begin = 0;

    // parse list of statements
    while (statement_begin < tokens.size())
    {

        // check for first letter
        //  - `IF`
        //  - `FOR` ect
        if (tokens[statement_begin].type == Lexer::TokenType::IF)
        {
            // TODO: IF statement
        }
        if (tokens[statement_begin].type == Lexer::TokenType::FOR)
        {
            // TODO: IF statement
        }

        // this must be asignment or empty statement;
        // `expr := expr ;`
        // `expr ;`
        // `;`
        {
            int semicolon_pos = FindToken(tokens, statement_begin, Lexer::TokenType::SEMICOLON);
            if (semicolon_pos == -1)
            {
                err.emplace_back("Missing semicolon at the end of statement");
                return statement_list;
            }
            Lexer::TokenList statement_tokens = SubVector(tokens, statement_begin, semicolon_pos);
            AST::StatementPtr stmt = ParseStatement(err, statement_tokens);
            statement_list.push_back(stmt);
            statement_begin = semicolon_pos + 1;
        }
    }

    return statement_list;
}

///////////////////////////

std::vector<AST::VariableDeclaration> ParseVarInput(ErrorList_t &err, Lexer::TokenList tokens)
{
    if (tokens.size() == 0)
    {
        return {};
    }

    // First token must be VAR_INPUT
    if (!IsTokenInPosition(tokens, 0, Lexer::TokenType::VAR_INPUT))
    {
        err.emplace_back("Expected VAR_INPUT keyword");
        return {};
    }

    // last token must be END_VAR
    if (tokens.back().type != Lexer::TokenType::END_VAR)
    {
        err.emplace_back("Expected END_VAR keyword");
        return {};
    }

    // parse block body
    return ParseVarBody(err, SubVector(tokens, 1, tokens.size() - 2));
}

std::vector<AST::VariableDeclaration> ParseVarOutput(ErrorList_t &err, Lexer::TokenList tokens)
{
    if (tokens.size() == 0)
    {
        return {};
    }

    // First token must be VAR_OUTPUT
    if (!IsTokenInPosition(tokens, 0, Lexer::TokenType::VAR_OUTPUT))
    {
        err.emplace_back("Expected VAR_OUTPUT keyword");
        return {};
    }

    // last token must be END_VAR
    if (tokens.back().type != Lexer::TokenType::END_VAR)
    {
        err.emplace_back("Expected END_VAR keyword");
        return {};
    }

    // parse block body
    return ParseVarBody(err, SubVector(tokens, 1, tokens.size() - 2));
}

std::vector<AST::VariableDeclaration> ParseVarInOut(ErrorList_t &err, Lexer::TokenList tokens)
{
    if (tokens.size() == 0)
    {
        return {};
    }

    // First token must be VAR_IN_OUT
    if (!IsTokenInPosition(tokens, 0, Lexer::TokenType::VAR_IN_OUT))
    {
        err.emplace_back("Expected VAR_IN_OUT keyword");
        return {};
    }

    // last token must be END_VAR
    if (tokens.back().type != Lexer::TokenType::END_VAR)
    {
        err.emplace_back("Expected END_VAR keyword");
        return {};
    }

    // parse block body
    return ParseVarBody(err, SubVector(tokens, 1, tokens.size() - 2));
}

std::vector<AST::VariableDeclaration> ParseVar(ErrorList_t &err, Lexer::TokenList tokens)
{
    if (tokens.size() == 0)
    {
        return {};
    }

    // First token must be VAR
    if (!IsTokenInPosition(tokens, 0, Lexer::TokenType::VAR))
    {
        err.emplace_back("Expected VAR keyword");
        return {};
    }

    // last token must be END_VAR
    if (tokens.back().type != Lexer::TokenType::END_VAR)
    {
        err.emplace_back("Expected END_VAR keyword");
        return {};
    }

    // parse block body
    return ParseVarBody(err, SubVector(tokens, 1, tokens.size() - 2));
}

///////////////////////////

bool ParseVarDeclaration(ErrorList_t &err, Lexer::TokenList tokens, AST::VariableDeclaration *var)
{
    // ;
    // name : data_type;
    // name : datatype := expr;

    if (tokens.size() == 0)
    {
        // no code emited
        return {};
    }

    if (tokens.size() == 1)
    {
        if (tokens[0].type == Lexer::TokenType::SEMICOLON)
        {
            // empty variable declaration
            // no error
            // no code emited
            return false;
        }
    }

    if (!IsIndexInBounds(tokens, 0) && tokens[0].type != Lexer::TokenType::IDENTIFIER)
    {
        err.emplace_back("Expected Identifier (variable name)");
        return false;
    }

    if (!IsIndexInBounds(tokens, 1) && tokens[1].type != Lexer::TokenType::COLON)
    {
        err.emplace_back("Expected : ");
        return false;
    }

    if (!IsIndexInBounds(tokens, 2) && tokens[2].type != Lexer::TokenType::IDENTIFIER)
    {
        err.emplace_back("Expected Identifier (variable data type)");
        return false;
    }

    std::string name = tokens[0].str;
    std::string data_type = tokens[2].str;

    // there should be := or ;

    if (!IsIndexInBounds(tokens, 3) &&
        (tokens[3].type != Lexer::TokenType::ASSIGN ||
         tokens[3].type != Lexer::TokenType::SEMICOLON))
    {
        err.emplace_back("Expected Identifier (variable data type)");
        return false;
    }

    if (IsIndexInBounds(tokens, 3) && tokens[3].type == Lexer::TokenType::SEMICOLON)
    {
        AST::DataType type = AST::StringToDataType(data_type);
        if(type == AST::DataType::UNNOWN){
            err.emplace_back("\'" + data_type + "\' is not valid data type");
            return false;
        }
        *var = AST::VariableDeclaration(name, type);
        return true;
    }

    if (IsIndexInBounds(tokens, 3) && tokens[3].type == Lexer::TokenType::ASSIGN)
    {

        int semicolon_pos = FindToken(tokens, 3, Lexer::TokenType::SEMICOLON);
        if (semicolon_pos == -1)
        {
            err.emplace_back("Missing semicolon at the end of variable declaration");
            return false;
        }

        Lexer::TokenList expr_tokens = SubVector(tokens, 4, semicolon_pos - 1);
        AST::ExprPtr initial_value = ParseExpression(err, expr_tokens);
        

        AST::DataType type = AST::StringToDataType(data_type);
        if(type == AST::DataType::UNNOWN){
            err.emplace_back("\'" + data_type + "\' is not valid data type");
            return false;
        }
        *var = AST::VariableDeclaration(name, type, initial_value);
        return true;
    }

    err.emplace_back("Internal compiler error");
    return false;
}

std::vector<AST::VariableDeclaration> ParseVarBody(ErrorList_t &err, Lexer::TokenList tokens)
{
    // name : data_type;
    // name : datatype := expr;

    if (tokens.size() == 0)
    {
        // no code emited
        return {};
    }

    std::vector<AST::VariableDeclaration> variables;

    int begin_var_pos = 0;
    while (begin_var_pos < tokens.size())
    {
        int semicolon_pos = FindToken(tokens, begin_var_pos, Lexer::TokenType::SEMICOLON);

        if (semicolon_pos == -1)
        {
            err.emplace_back("Missing semicolon at end of variable declaration");
            break;
        }

        Lexer::TokenList var_tokens = SubVector(tokens, begin_var_pos, semicolon_pos);

        AST::VariableDeclaration var;
        if (ParseVarDeclaration(err, var_tokens, &var))
        {
            variables.push_back(var);
        }
        begin_var_pos = semicolon_pos + 1;
    }

    return variables;
}

/////////////////////////////////

// TODO
AST::StatementPtr ParseStatement(ErrorList_t &err, const Lexer::TokenList &tokens)
{
    if (tokens.size() == 0)
    {
        return AST::EmptyStatement::Make(); // no statement was provided (no code emited)
    }

    if (tokens.back().type != Lexer::TokenType::SEMICOLON)
    {
        err.emplace_back("Missing semicolon at the end of statement");
        return AST::EmptyStatement::Make();
    }

    if (tokens.size() == 1)
    {
        return AST::EmptyStatement::Make(); // provided empty statement (no code emited)
    }

    // scan for assignment operator;
    int assign_pos = FindToken(tokens, Lexer::TokenType::ASSIGN);

    if (assign_pos == -1)
    {
        // not assigned expression
        // stil parse as expression to find syntax errors
        Lexer::TokenList expr_tokens = SubVector(tokens, 0, tokens.size() - 2); // cut semicolon
        AST::ExprPtr expr = ParseExpression(err, expr_tokens);
        if (expr == nullptr)
        {
            return AST::EmptyStatement::Make();
        }

        return AST::ExprStatement::Make(expr);
    }
    else
    {
        Lexer::TokenList left_tokens = SubVector(tokens, 0, assign_pos - 1);
        Lexer::TokenList right_tokens = SubVector(tokens, assign_pos + 1, tokens.size() - 2);
        AST::ExprPtr expr_l = ParseExpression(err, left_tokens);
        AST::ExprPtr expr_r = ParseExpression(err, right_tokens);

        if (expr_l == nullptr)
        {
            return AST::EmptyStatement::Make();
        }

        if (expr_r == nullptr)
        {
            return AST::EmptyStatement::Make();
        }

        return AST::AssignmentStatement::Make(expr_l, expr_r);
    }
}

/////////////////////////////////

struct OperatorType
{
    enum class Type
    {
        ERROR,

        INFIX,
        PREFIX,
        POSTFIX,
    };

    Type type;
    Lexer::TokenType token;
    int priority;

    OperatorType(Type _type, Lexer::TokenType _token, int _priority) : type(_type),
                                                                       token(_token),
                                                                       priority(_priority) {}

    bool operator==(OperatorType op)
    {
        return (type == op.type) &&
               (token == op.token) &&
               (priority == op.priority);
    }
};

OperatorType operator_types_list[] = {
    {OperatorType::Type::POSTFIX, Lexer::TokenType::DEREFERENCE, 9},    // ex "^"
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

bool IsValidOperator(OperatorType op)
{
    constexpr int operator_types_list_size = sizeof(operator_types_list) / sizeof(operator_types_list[0]);

    for (int i = 0; i < operator_types_list_size; i++)
    {
        if (operator_types_list[i] == op)
        {
            return true;
        }
    }

    return false;
}

bool IsValidOperator(AST::ExprPtr left, AST::ExprPtr right, Lexer::TokenType token, int precedence)
{
    bool is_prefix = left == nullptr && right != nullptr;
    bool is_postfix = left != nullptr && right == nullptr;
    bool is_infix = left != nullptr && right != nullptr;

    if (is_prefix)
        return IsValidOperator({OperatorType::Type::PREFIX, token, precedence});
    if (is_postfix)
        return IsValidOperator({OperatorType::Type::POSTFIX, token, precedence});
    if (is_infix)
        return IsValidOperator({OperatorType::Type::INFIX, token, precedence});

    return false;
}

AST::ExprPtr ParseOperator(AST::ExprPtr left, AST::ExprPtr right, Lexer::TokenType token)
{

    bool is_prefix = left == nullptr && right != nullptr;
    bool is_postfix = left != nullptr && right == nullptr;
    bool is_infix = left != nullptr && right != nullptr;

    AST::ExprPtr expr = nullptr;

    // if (is_postfix && token == Lexer::TokenType::DEREFERENCE)
    if (is_prefix && token == Lexer::TokenType::MINUS)
        expr = AST::UnaryMinus::Make(right);
    if (is_prefix && token == Lexer::TokenType::PLUS)
        expr = AST::UnaryPlus::Make(right);
    if (is_prefix && token == Lexer::TokenType::NEGATION)
        expr = AST::BooleanNOT::Make(right);
    if (is_infix && token == Lexer::TokenType::EXPONENTIATION)
        expr = AST::Exponentiation::Make(left, right);
    if (is_infix && token == Lexer::TokenType::MULTIPLY)
        expr = AST::Multiply::Make(left, right);
    if (is_infix && token == Lexer::TokenType::DIVIDE)
        expr = AST::Divide::Make(left, right);
    if (is_infix && token == Lexer::TokenType::MODULO)
        expr = AST::Modulo::Make(left, right);
    if (is_infix && token == Lexer::TokenType::PLUS)
        expr = AST::Add::Make(left, right);
    if (is_infix && token == Lexer::TokenType::MINUS)
        expr = AST::Subtract::Make(left, right);
    if (is_infix && token == Lexer::TokenType::GREATER_THAN)
        expr = AST::GreaterThan::Make(left, right);
    if (is_infix && token == Lexer::TokenType::LESS_THAN)
        expr = AST::LessThan::Make(left, right);
    if (is_infix && token == Lexer::TokenType::GREATER_OR_EQUAL)
        expr = AST::GreaterOrEqual::Make(left, right);
    if (is_infix && token == Lexer::TokenType::LESS_OR_EQUAL)
        expr = AST::LessOrEqual::Make(left, right);
    if (is_infix && token == Lexer::TokenType::EQUALITY)
        expr = AST::Equality::Make(left, right);
    if (is_infix && token == Lexer::TokenType::INEQUALITY)
        expr = AST::Inequality::Make(left, right);
    if (is_infix && token == Lexer::TokenType::BOOLEAN_AND)
        expr = AST::BooleanAND::Make(left, right);
    if (is_infix && token == Lexer::TokenType::BOOLEAN_XOR)
        expr = AST::BooleanXOR::Make(left, right);
    if (is_infix && token == Lexer::TokenType::BOOLEAN_OR)
        expr = AST::BooleanOR::Make(left, right);

    return expr;
}

AST::ExprPtr ParseExpression(ErrorList_t &err, const Lexer::TokenList &tokens)
{

    if (tokens.size() == 0)
    {
        err.emplace_back("Empty Expression");
        return nullptr;
    }

    // step 1 copy to variant table
    std::vector<std::variant<Lexer::Token, AST::ExprPtr>> token_expr_vec;
    for (int i = 0; i < tokens.size(); i++)
    {
        // TODO: Parse function call;
        if (tokens[i].type == Lexer::TokenType::IDENTIFIER)
        {
            // step 1.1 parse variable
            token_expr_vec.push_back(ParseVariable(err, tokens[i]));
            continue;
        }
        if (IsTokenLiteral(tokens[i].type))
        {
            // step 1.2 parse literals
            token_expr_vec.push_back(ParseNumericLiteral(err, tokens[i]));
            continue;
        }

        token_expr_vec.push_back(tokens[i]);
    }

    if (token_expr_vec.size() == 1)
    {
        AST::ExprPtr *expr = std::get_if<AST::ExprPtr>(&token_expr_vec.front());
        if (expr == nullptr)
        {
            // invalid expression
            err.emplace_back("Invalid expression");
            return nullptr;
        }

        // can stop there - emit produced code;
        return *expr;
    }

    // step 2 parse operators
    for (int precedence = 11; precedence > 0; precedence--)
    {
        for (int index = 0; index < token_expr_vec.size(); index++)
        {
            // check if token_expr_vec[i] is token and not an expression
            Lexer::Token *token = std::get_if<Lexer::Token>(&token_expr_vec[index]);
            if (token == nullptr)
                continue;

            AST::ExprPtr left = nullptr;
            AST::ExprPtr right = nullptr;

            // get left and right side of operator
            if (IsIndexInBounds(token_expr_vec, index - 1))
            {
                AST::ExprPtr *tmp = nullptr;
                tmp = std::get_if<AST::ExprPtr>(&token_expr_vec[index - 1]);
                if (tmp != nullptr)
                    left = *tmp;
            }
            if (IsIndexInBounds(token_expr_vec, index + 1))
            {
                AST::ExprPtr *tmp = nullptr;
                tmp = std::get_if<AST::ExprPtr>(&token_expr_vec[index + 1]);
                if (tmp != nullptr)
                    right = *tmp;
            }

            // check if operator exists
            if (!IsValidOperator(left, right, token->type, precedence))
                continue;

            // parse operator
            AST::ExprPtr expr = ParseOperator(left, right, token->type);
            if (expr == nullptr)
                continue;

            // here we sucessfuly parsed operator
            // time to copy result token_expr_vec and clean unnecessary tokens

            token_expr_vec[index] = expr;
            if (right != nullptr)
                token_expr_vec.erase(token_expr_vec.begin() + index + 1);

            if (left != nullptr)
                token_expr_vec.erase(token_expr_vec.begin() + index - 1);

            // restart loop if parsed succesfully
            index = 0;
        }
    }

    if (token_expr_vec.size() != 1)
    {
        err.emplace_back("Invalid expression");
        return nullptr;
    }

    AST::ExprPtr *expr = std::get_if<AST::ExprPtr>(&token_expr_vec.front());
    if (expr == nullptr)
    {
        // invalid expression
        err.emplace_back("Invalid expression");
        return nullptr;
    }

    // can stop there - emit produced code;
    return *expr;
}

AST::ExprPtr ParseVariable(ErrorList_t &err, Lexer::Token token)
{
    if (token.type != Lexer::TokenType::IDENTIFIER)
    {
        err.emplace_back("Expected variable identifier");
        return nullptr;
    }

    return AST::Variable::CreateVariable(token.str);
}

void SplitNumericLiteral(
    ErrorList_t &err,
    std::string token,
    std::string *type,
    std::string *base_str,
    std::string *number_str,
    bool *has_type,
    bool *has_base)
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
        *has_type = true;
        *has_base = true;
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
            *has_type = false;
            *has_base = true;
            return;
        }
        else
        {
            *type = token.substr(0, first_hash);
            *base_str = "";
            *number_str = token.substr(first_hash + 1);
            *has_type = true;
            *has_base = false;
            return;
        }
    }

    else if (first_hash < 0 && second_hash < 0)
    {
        // number must be REAL or INT base 10
        *type = "";
        *base_str = "";
        *number_str = token;
        *has_type = false;
        *has_base = false;
        return;
    }

    // error case
    *type = "";
    *base_str = "";
    *number_str = "";
    *has_type = false;
    *has_base = false;
    err.emplace_back("error: invalid numeric literal \n");
}

template <typename T>
void ParseInteger(ErrorList_t &err, std::string str, int base, T *result)
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
        err.push_back("error: \"" + str + "\" is not valid base " + std::to_string(base) + " number. \n");
        return;
    }
}

template <typename T>
void ParseFloat(ErrorList_t &err, std::string str, int base, T *result)
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
AST::ExprPtr ParseNumericLiteral(ErrorList_t &err, Lexer::Token token)
{
    std::string type;
    std::string base_str;
    std::string number_str;
    bool has_type = false;
    bool has_base = false;
    SplitNumericLiteral(err, token.str, &type, &base_str, &number_str, &has_type, &has_base);

    int64_t base = 10;
    if (has_base)
    {
        ParseInteger<int64_t>(err, base_str, 10, &base);
    }

    if (base < 2 || base > 36)
    {
        err.emplace_back("Error : base must be in range [2, 36]");
        return AST::LiteralSpecific::Create_INT(0);
    }

    // ambiguous type
    if (!has_type)
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

    if (has_type)
    {

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

template <typename T_vec>
bool IsIndexInBounds(T_vec vec, int index)
{
    return (index >= 0) && (index < vec.size());
}

bool IsTokenInPosition(const Lexer::TokenList &tokens, int index, Lexer::TokenType type)
{
    if (index >= tokens.size())
        return false;
    if (index < 0)
        return false;
    if (tokens[index].type != type)
        return false;

    return true;
}
