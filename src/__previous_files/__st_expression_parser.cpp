#include "st_expression_parser.hpp"

#include "../ast.hpp"
#include "../lexer/st_lexer.hpp"
#include <variant>
#include <vector>
#include <list>
#include <charconv>
#include <utility>

int FindKeyword(
    const std::vector<Lexer::Token> &tokens,
    int begin,
    Lexer::TokenType keyword);

int FindKeyword(
    const std::vector<Lexer::Token> &tokens,
    Lexer::TokenType keyword);

bool ParseStatementList(std::vector<Error> *err, std::vector<Lexer::Token> tokens, AST::StatementList* stmt_list)
{

    // statement types
    // 0. expression not assigned (error case)
    // >>>  expression;
    //
    // 1. assignment
    // >>> variable := expression;
    //
    // 2. condition
    // >>> IF Condition THEN
    // >>>    ...
    // >>> END_IF;
    //
    //

    int index = 0;
    while (index < tokens.size())
    {
        if (tokens[index].type == Lexer::TokenType::IF)
        {
            if(ParseIfStatement(err, tokens, index, &index)){

            }
            continue;
        }

        // Parse assignment statement
        AST::StatementPtr stmt;
        if(ParseSimpleStatement(err, tokens, index, &index, &stmt)){
            stmt_list->push_back(stmt);
        }
    }

    return true;
}

std::vector<Lexer::Token> FindIfStatementRange(const std::vector<Lexer::Token> &tokens, int begin)
{

    if (tokens[begin].type != Lexer::TokenType::IF)
    {
        return {};
    }

    int nested_if_counter = 0;

    for (int i = begin + 1; i < tokens.size(); i++)
    {
        if (tokens[i].type == Lexer::TokenType::IF)
        {
            nested_if_counter++;
            continue;
        }

        if (tokens[i].type == Lexer::TokenType::END_IF)
        {
            if (nested_if_counter > 0)
            {
                nested_if_counter--;
                continue;
            }
            else
            {
                std::vector<Lexer::Token> if_statement{&tokens[begin], &tokens[i] + 1};
                return if_statement;
            }
        }
    }

    return {};
}

// TODO: finish this
bool ParseIfStatement(std::vector<Error> *err, const std::vector<Lexer::Token> &tokens, int begin_index, int *next_stmt_index)
{

    if (tokens[begin_index].type != Lexer::TokenType::IF)
    {
        // throw error
        return false;
    }

    // >>> IF Condition THEN
    // >>>     StatementList1 [possible nested keywords: `IF`, `THEN`, `ELSIF`, `THEN`, `ELSE`, `END_IF`]
    // >>> ELSIF Condition2 THEN
    // >>>     StatementList2 [possible nested keywords: `IF`, `THEN`, `ELSIF`, `THEN`, `ELSE`, `END_IF`]
    // >>> ELSE
    // >>>     StatementList3 [possible nested keywords: `IF`, `THEN`, `ELSIF`, `THEN`, `ELSE`, `END_IF`]
    // >>> END_IF;

    // count nested IF statements
    // increase on: `IF`
    // decrease on: `END_IF`
    // ignore keywords if counter != 0: `IF`, `THEN`, `ELSIF`, `THEN`, `ELSE`, `END_IF`
    int nested_if_counter = 0;

    int previous_keyword_index = begin_index;

    for (int i = begin_index + 1; i < tokens.size(); i++)
    {

        // process possibility of nested if

        if (tokens[i].type == Lexer::TokenType::IF)
        {
            nested_if_counter++;
            continue;
        }

        if (nested_if_counter != 0)
        {
            if (tokens[i].type == Lexer::TokenType::END_IF)
            {
                nested_if_counter--;
            }
            continue;
        }

        Lexer::TokenType prev = tokens[previous_keyword_index].type;
        Lexer::TokenType curr = tokens[i].type;

        // conditions
        // IF {Expression} THEN
        if (prev == Lexer::TokenType::IF && curr == Lexer::TokenType::THEN)
        {
            std::vector<Lexer::Token> first_condition{&tokens[previous_keyword_index] + 1, &tokens[i]};
            // ParseExpression(err, first_condition);
            previous_keyword_index = i;
            continue;
        }

        // ELSIF {Expression} THEN
        if (prev == Lexer::TokenType::ELSIF && curr == Lexer::TokenType::THEN)
        {
            std::vector<Lexer::Token> condition{&tokens[previous_keyword_index] + 1, &tokens[i]};
            // ParseExpression(err, condition);
            previous_keyword_index = i;
            continue;
        }

        // statement lists
        // THEN {statement list} ELSIF
        if (prev == Lexer::TokenType::THEN && curr == Lexer::TokenType::ELSIF)
        {
            std::vector<Lexer::Token> expr_list{&tokens[previous_keyword_index] + 1, &tokens[i]};
            // ParseStatementList(err, expr_list);
            previous_keyword_index = i;
            continue;
        }

        // THEN {statement list} ELSE
        if (prev == Lexer::TokenType::THEN && curr == Lexer::TokenType::ELSE)
        {
            std::vector<Lexer::Token> expr_list{&tokens[previous_keyword_index] + 1, &tokens[i]};
            // ParseStatementList(err, expr_list);
            previous_keyword_index = i;
            continue;
        }

        // THEN {statement list} END_IF
        if (prev == Lexer::TokenType::THEN && curr == Lexer::TokenType::END_IF)
        {
            std::vector<Lexer::Token> expr_list{&tokens[previous_keyword_index] + 1, &tokens[i]};
            // ParseStatementList(err, expr_list);
            previous_keyword_index = i;

            *next_stmt_index = i;
            break;
        }

        // ELSE {statement list} END_IF
        if (prev == Lexer::TokenType::ELSE && curr == Lexer::TokenType::END_IF)
        {
            std::vector<Lexer::Token> expr_list{&tokens[previous_keyword_index] + 1, &tokens[i]};
            // ParseStatementList(err, expr_list);
            previous_keyword_index = i;

            *next_stmt_index = i;
            break;
        }
    }

    // after END_IF must be semicolon

    if (tokens[previous_keyword_index].type != Lexer::TokenType::END_IF)
    {
        return false; // throw error
    }

    if (tokens[previous_keyword_index + 1].type != Lexer::TokenType::SEMICOLON)
    {
        return false; // throw error
    }

    *next_stmt_index = previous_keyword_index + 1;

    return true;
}

bool ParseSimpleStatement(std::vector<Error> *err, const std::vector<Lexer::Token> &tokens, int begin_index, int *next_stmt_index, AST::StatementPtr* stmt_ptr)
{

    // step 1 - semicolon
    int semicolon_index = FindKeyword(tokens, begin_index, Lexer::TokenType::SEMICOLON);
    if (semicolon_index < 0)
    {
        *next_stmt_index = tokens.size();
        return false; // todo throw error
    }

    *next_stmt_index = semicolon_index + 1;

    // step 1 - assignment operator
    int assign_index = FindKeyword(tokens, begin_index, Lexer::TokenType::ASSIGN);

    if (semicolon_index < assign_index || assign_index < 0)
    {
        return false; // todo throw error
    }

    // split for part before and after assignment operator
    // {Expression1} := {Expression2} ;

    std::vector<Lexer::Token> expr1_tokens{&tokens[begin_index], &tokens[assign_index]};
    std::vector<Lexer::Token> expr2_tokens{&tokens[assign_index] + 1, &tokens[semicolon_index]};

    AST::ExprPtr expr1;
    AST::ExprPtr expr2;

    ParseExpression(err, expr1_tokens, &expr1);
    ParseExpression(err, expr2_tokens, &expr2);

    AST::AssignStatement statement{expr1, expr2};
    *stmt_ptr = std::make_shared<AST::AssignStatement>(statement);

    return true;
}

struct OperatorPriority
{
    int priority;
    bool expr_on_left;
    bool expr_on_right;
    Lexer::TokenType token_type;
    AST::Operation operation;

    constexpr OperatorPriority(int _priority,
                               bool _expr_on_left,
                               bool _expr_on_right,
                               Lexer::TokenType _token_type,
                               AST::Operation _operation)
        : priority(_priority),
          expr_on_left(_expr_on_left),
          expr_on_right(_expr_on_right),
          token_type(_token_type),
          operation(_operation) {}

    bool IsSameOperation(int _priority,
                         bool _expr_on_left,
                         bool _expr_on_right,
                         Lexer::TokenType _token_type) const
    {
        return (priority == _priority) &&
               (expr_on_left == _expr_on_left) &&
               (expr_on_right == _expr_on_right) &&
               (token_type == _token_type);
    }

    bool IsBinary() const
    {
        return expr_on_left && expr_on_right;
    }

    bool IsUnary() const
    {
        return expr_on_left != expr_on_right;
    }
};

constexpr OperatorPriority operotor_priority_list[] =
    {
        OperatorPriority{1, true, true, Lexer::TokenType::BOOLEAN_OR, AST::Operation::BOOLEAN_OR},
        OperatorPriority{2, true, true, Lexer::TokenType::BOOLEAN_XOR, AST::Operation::BOOLEAN_XOR},
        OperatorPriority{3, true, true, Lexer::TokenType::BOOLEAN_AND, AST::Operation::BOOLEAN_AND},
        OperatorPriority{4, true, true, Lexer::TokenType::GREATER_THAN, AST::Operation::GREATER_THAN},
        OperatorPriority{4, true, true, Lexer::TokenType::LESS_THAN, AST::Operation::LESS_THAN},
        OperatorPriority{4, true, true, Lexer::TokenType::GREATER_OR_EQUAL, AST::Operation::GREATER_OR_EQUAL},
        OperatorPriority{4, true, true, Lexer::TokenType::LESS_OR_EQUAL, AST::Operation::LESS_OR_EQUAL},
        OperatorPriority{4, true, true, Lexer::TokenType::EQUALITY, AST::Operation::EQUALITY},
        OperatorPriority{4, true, true, Lexer::TokenType::INEQUALITY, AST::Operation::INEQUALITY},
        OperatorPriority{5, true, true, Lexer::TokenType::PLUS, AST::Operation::ADD},
        OperatorPriority{5, true, true, Lexer::TokenType::MINUS, AST::Operation::SUBTRACT},
        OperatorPriority{6, true, true, Lexer::TokenType::MULTIPLY, AST::Operation::MULTIPLY},
        OperatorPriority{6, true, true, Lexer::TokenType::DIVIDE, AST::Operation::DIVIDE},
        OperatorPriority{6, true, true, Lexer::TokenType::MODULO, AST::Operation::MODULO},
        OperatorPriority{7, true, true, Lexer::TokenType::EXPONENTIATION, AST::Operation::EXPONENTIATION},
        OperatorPriority{8, false, true, Lexer::TokenType::PLUS, AST::Operation::UNARY_PLUS},         // unary
        OperatorPriority{8, false, true, Lexer::TokenType::MINUS, AST::Operation::UNARY_MINUS},       // unary
        OperatorPriority{8, false, true, Lexer::TokenType::NEGATION, AST::Operation::BOOLEAN_NOT},    // unary
        OperatorPriority{9, true, false, Lexer::TokenType::DEREFERENCE, AST::Operation::DEREFERENCE}, // unary
};

const OperatorPriority *FindOperatorWithPriority(int priority, bool expr_on_left,
                                                 bool expr_on_right,
                                                 Lexer::TokenType token_type)
{
    constexpr int operotor_priority_list_size =
        sizeof(operotor_priority_list) / sizeof(operotor_priority_list[0]);

    for (int i = 0; i < operotor_priority_list_size; i++)
    {

        const OperatorPriority *op = &operotor_priority_list[i];
        if (op->IsSameOperation(priority, expr_on_left, expr_on_right, token_type))
        {
            return op;
        }
    }

    return nullptr;
}

bool ParseExpression(std::vector<Error> *err, const std::vector<Lexer::Token> &tokens, AST::ExprPtr* expr)
{

    std::list<TokenExprVariant> token_variant_list;
    token_variant_list.insert(token_variant_list.end(), tokens.begin(), tokens.end());

    // step 1: parse literals
    ParseExprLiterals(err, &token_variant_list);

    // step 1.2: parse variable names
    ParseVariableExpr(err, &token_variant_list);

    // step 2: parse brackets

    // step 3: parse function calls

    // step 4: parse binary and unary operators

    for (int current_priority = 11; current_priority > 0; current_priority--)
    {
        ParseOperatorsWithPriority(err, current_priority, &token_variant_list);
    }

    // return result 
    if(token_variant_list.size() != 1){
        err->emplace_back("Invalid Expression, at: " + tokens[0].pos.ToString());
        return false;
    }

    AST::ExprPtr expr1 = token_variant_list.begin()->GetExpr();
    if(expr1 == nullptr){
        err->emplace_back("Invalid Expression, at: " + tokens[0].pos.ToString());
        return false;
    }

    *expr = expr1;
    return true;

}

bool ParseVariableExpr(std::vector<Error> *err, std::list<TokenExprVariant> *token_variant_list)
{

    for (auto iter = token_variant_list->begin(); iter != token_variant_list->end(); iter++)
    {
        Lexer::Token *token = iter->GetToken();

        if (token != nullptr)
        {
            if (token->type == Lexer::TokenType::IDENTIFIER)
            {

                AST::ExprPtr var = std::make_shared<AST::VariableAccess>(token->str);
                (*iter) = var;
                // ParseNumericLiteral(err, &*iter);
            }
        }
    }

    return true;
}

bool ParseOperatorsWithPriority(std::vector<Error> *err, int current_priority, std::list<TokenExprVariant> *token_variant_list)
{
    // iterate over token list to convert operator with current priority
    while (true)
    {

        bool found_expr_with_given_priority = false;

        for (auto iter = token_variant_list->begin();
             iter != token_variant_list->end();
             iter++)
        {

            auto iter_expr_left = iter;
            auto iter_operator = iter;
            auto iter_expr_right = iter;

            // bool is_expr_on_left = false;
            // bool is_expr_on_right = false;

            // AST::ExprPtr expr_left = iter_expr_left->GetExpr();
            // Lexer::Token *_operator = iter_operator->GetToken();
            // AST::ExprPtr expr_right = iter_expr_right->GetExpr();

            AST::ExprPtr expr_left = nullptr;
            AST::ExprPtr expr_right = nullptr;
            Lexer::Token *_operator = iter_operator->GetToken();

            if (iter_operator == token_variant_list->end())
            {
                continue;
            }

            if (iter_expr_left != token_variant_list->begin())
            {
                iter_expr_left--;
                expr_left = iter_expr_left->GetExpr();
            }

            iter_expr_right++;
            if (iter_expr_right != token_variant_list->end())
            {
                expr_right = iter_expr_right->GetExpr();
            }

            if (_operator == nullptr)
            {
                continue;
            }

            bool is_expr_on_left = expr_left != nullptr;
            bool is_expr_on_right = expr_right != nullptr;

            Lexer::TokenType token_type = _operator->type;

            const OperatorPriority *op = FindOperatorWithPriority(current_priority, is_expr_on_left, is_expr_on_right, token_type);

            if (op == nullptr)
            {
                continue;
            }

            // insert computed operator
            if (expr_left && !expr_right)
            {
                AST::ExprPtr e = std::make_shared<AST::Unary>(op->operation, expr_left);
                *iter_operator = e;
            }

            if (!expr_left && expr_right)
            {
                AST::ExprPtr e = std::make_shared<AST::Unary>(op->operation, expr_right);
                *iter_operator = e;
            }

            if (expr_left && expr_right)
            {
                AST::ExprPtr e = std::make_shared<AST::Binary>(op->operation, expr_left, expr_right);
                *iter_operator = e;
            }

            // remove processed tokens

            if (is_expr_on_left)
            {
                token_variant_list->erase(iter_expr_left);
            }
            if (is_expr_on_right)
            {
                token_variant_list->erase(iter_expr_right);
            }

            found_expr_with_given_priority = true;
            break;
        }

        if (!found_expr_with_given_priority)
        {
            break;
        }
    }

    return false;
}

/// `GetBinaryExprOperands()` is used to check if there is valid operator in sequence and extract expressions
///
///
/// ```markdown
///                     begin
///                     | begin + 1
///                     | | begin + 2
///                     | | |
///                     V V V
///        155.0 + 34 * 5 / 1.3 * (3 + 10)
///                     ^ ^ ^
///                     | | |
///                     | | expr2
///                     | Token (operator)
///                     expr1
/// ```
bool GetBinaryExprOperator(
    std::vector<Error> *err,
    std::list<TokenExprVariant> *tokens,
    std::list<TokenExprVariant>::iterator begin,
    Lexer::TokenType *_operator,
    AST::ExprPtr *expression1,
    AST::ExprPtr *expression2)
{

    std::list<TokenExprVariant>::iterator iter = begin;

    if (iter == tokens->end())
    {
        return false;
    }

    TokenExprVariant expr1_variant = *iter;

    iter++;
    if (iter == tokens->end())
    {
        return false;
    }

    TokenExprVariant operator_variant = *iter;

    iter++;
    if (iter == tokens->end())
    {
        return false;
    }

    TokenExprVariant expr2_variant = *iter;

    AST::ExprPtr expr1 = expr1_variant.GetExpr();
    AST::ExprPtr expr2 = expr2_variant.GetExpr();
    Lexer::Token *operator_token = operator_variant.GetToken();

    // if (expr1 == nullptr)
    // {
    //     return false;
    // }
    // if (expr2 == nullptr)
    // {
    //     return false;
    // }
    if (operator_token == nullptr)
    {
        return false;
    }

    *expression1 = expr1;
    *expression2 = expr2;
    *_operator = operator_token->type;

    return true;
}

bool ParseExprLiterals(std::vector<Error> *err, std::list<TokenExprVariant> *token_variant_list)
{

    for (auto iter = token_variant_list->begin(); iter != token_variant_list->end(); iter++)
    {
        Lexer::Token *token = iter->GetToken();

        if (token != nullptr)
        {
            if (token->type == Lexer::TokenType::NUMERIC_LITERAL)
            {
                ParseNumericLiteral(err, &*iter);
            }
        }
    }

    return true;
}

bool ParseNumericLiteral(std::vector<Error> *err, TokenExprVariant *token_and_expr)
{
    if (token_and_expr == nullptr)
    {
        err->emplace_back(Error::ErrorType::UNNOWN,
                          "Internal compiler error - this is caused because creator of this compiler is a moron.");
        return false;
    }

    Lexer::Token *token = token_and_expr->GetToken();

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
            AST::ExprPtr e1 = std::make_shared<AST::Literal>(AST::Literal(number));
            *token_and_expr = e1;
            return true;
        }
    }

    else

    { // try conversion to integer
        int64_t number = 0;
        std::from_chars_result result = std::from_chars(first, last, number);
        if (result.ec == std::errc())
        {
            AST::ExprPtr e1 = std::make_shared<AST::Literal>(AST::Literal(number));
            *token_and_expr = e1;
            return true;
        }
    }

    err->emplace_back(Error::ErrorType::UNNOWN,
                      "Cannot parse numeric literal + " + token->str + " + at position: " + token->pos.ToString());
    return false;
}
