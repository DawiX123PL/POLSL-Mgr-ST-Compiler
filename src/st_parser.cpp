#include "ast.hpp"
#include "st_parser.hpp"
#include "st_lexer.hpp"
#include <variant>
#include <vector>
#include <list>
#include <charconv>

std::vector<Error> Parse(const std::vector<Lexer::Token> &tokens, AST::Function* function)
{

    // std::list<TokenExprVariant> token_and_expr_list;

    std::vector<Error> err;

    // // construct token and expr list
    // for (int i = 0; i < tokens.size(); i++)
    // {
    //     token_and_expr_list.emplace_back(tokens[i]);
    // }

    // // 1. Parse numeric literals
    // for (auto iter = token_and_expr_list.begin(); iter != token_and_expr_list.end(); iter++)
    // {
    //     TokenExprVariant *token_expr = &(*iter);
    //     ParseNumericLiterals(token_expr, &err);
    // }

    // 2. Parse POUs definitions

    // AST::Function function;
    ParseFunction(&err, tokens, function);

    return err;
}


bool ParseFunction(std::vector<Error> *err, const std::vector<Lexer::Token> &tokens, AST::Function* function)
{

    // first line must be:
    //     1          2       3      4
    //     v          v       v      v
    // >>> FUNCTION function_name : return_type

    if (tokens[0].type != Lexer::TokenType::FUNCTION)
    {
        err->emplace_back("Missing FUNCTION keyword at beginning of function");
        return false;
    }

    if (tokens[1].type != Lexer::TokenType::IDENTIFIER)
    {
        err->emplace_back("Expected function name after FUNCTION keyword at: " +
                          tokens[1].pos.ToString() +
                          "\n example: 'FUNCTION " +
                          Console::Underline("FunctionName") +
                          ": BOOL' ");
        return false;
    }

    if (tokens[2].type != Lexer::TokenType::COLON)
    {
        err->emplace_back("Expected colon ':' after function name at: " +
                          tokens[2].pos.ToString() +
                          "\n example: 'FUNCTION FunctionName " +
                          Console::Underline(":") +
                          " BOOL' ");
        return false;
    }

    if (tokens[3].type != Lexer::TokenType::IDENTIFIER)
    {
        err->emplace_back("Expected colon data type at: " +
                          tokens[2].pos.ToString() +
                          "\n example: 'FUNCTION FunctionName : " +
                          Console::Underline("BOOL"));

        return false;
    }

    // Last line must be:
    //     1          2       3      4
    //     v          v       v      v
    // >>> END_FUNCTION

    if (tokens.back().type != Lexer::TokenType::END_FUNCTION)
    {
        err->emplace_back("Missing END_FUNCTION keyword at the end of function starting at: " + tokens[0].pos.ToString() +
                          "\n solution: add missing END_FUNCTION keyword\n   FUNCTION test_func : BOOL\n   ...\n   " + Console::Underline("END_FUNCTION"));

        return false;
    }

    // find variable declarations in top of function
    //
    // FUNCTION function_name : return_type
    //  >>> VAR_INPUT | VAR_OUTPUT | VAR_IN_OUT | VAR
    //  >>>     ...
    //  >>> END_VAR
    // ...

    bool has_var_input = false;
    bool has_var_output = false;
    bool has_var_in_out = false;
    bool has_var = false;

    std::vector<AST::VariableDefinition> var_input_vec;
    std::vector<AST::VariableDefinition> var_output_vec;
    std::vector<AST::VariableDefinition> var_in_out_vec;
    std::vector<AST::VariableDefinition> var_vec;

    int var_begin = 4;
    while (true)
    {

        if (tokens[var_begin].type != Lexer::TokenType::VAR_INPUT &&
            tokens[var_begin].type != Lexer::TokenType::VAR_OUTPUT &&
            tokens[var_begin].type != Lexer::TokenType::VAR_IN_OUT &&
            tokens[var_begin].type != Lexer::TokenType::VAR)
        {
            break;
        }

        if ((has_var_input && tokens[var_begin].type == Lexer::TokenType::VAR_INPUT) ||
            (has_var_output && tokens[var_begin].type == Lexer::TokenType::VAR_OUTPUT) ||
            (has_var_in_out && tokens[var_begin].type == Lexer::TokenType::VAR_IN_OUT) ||
            (has_var && tokens[var_begin].type == Lexer::TokenType::VAR))

        {

            err->emplace_back(
                "variable block " +
                std::string(Lexer::TokenTypeToString(tokens[var_begin].type)) +
                " ... END_VAR already exists. Consider deleting one or join them together");
        }

        if (tokens[var_begin].type == Lexer::TokenType::VAR_INPUT)
            has_var_input = true;
        if (tokens[var_begin].type == Lexer::TokenType::VAR_OUTPUT)
            has_var_output = true;
        if (tokens[var_begin].type == Lexer::TokenType::VAR_IN_OUT)
            has_var_in_out = true;
        if (tokens[var_begin].type == Lexer::TokenType::VAR)
            has_var = true;

        // find var end
        int var_end = FindKeyword(tokens, var_begin, Lexer::TokenType::END_VAR);
        if (var_end != 0)
        {
            // parse VAR body;
            std::vector<Lexer::Token> var_body{&tokens[var_begin + 1], &tokens[var_end]};

            std::vector<AST::VariableDefinition> var_list = ParseVarList(err, var_body);

            if (tokens[var_begin].type == Lexer::TokenType::VAR_INPUT)
                var_input_vec.insert(var_input_vec.end(), var_list.begin(), var_list.end());

            if (tokens[var_begin].type == Lexer::TokenType::VAR_OUTPUT)
                var_output_vec.insert(var_output_vec.end(), var_list.begin(), var_list.end());

            if (tokens[var_begin].type == Lexer::TokenType::VAR_IN_OUT)
                var_in_out_vec.insert(var_in_out_vec.end(), var_list.begin(), var_list.end());

            if (tokens[var_begin].type == Lexer::TokenType::VAR)
                var_vec.insert(var_vec.end(), var_list.begin(), var_list.end());
        }
        else
        {
            err->emplace_back("Missing END_VAR after variable declaration" +
                              std::string(Lexer::TokenTypeToString(tokens[var_begin].type)) +
                              " in function starting from: " + tokens[var_begin].pos.ToString());
        }

        var_begin = var_end + 1;
        continue;
    }

    std::string function_name = tokens[1].str;
    std::string return_type = tokens[3].str;

    {
        // check for duplicated variable names
        std::vector<AST::VariableDefinition> all_var_vec;
        all_var_vec.insert(all_var_vec.end(), var_input_vec.begin(), var_input_vec.end());
        all_var_vec.insert(all_var_vec.end(), var_output_vec.begin(), var_output_vec.end());
        all_var_vec.insert(all_var_vec.end(), var_in_out_vec.begin(), var_in_out_vec.end());
        all_var_vec.insert(all_var_vec.end(), var_vec.begin(), var_vec.end());

        for (int i = 0; i < all_var_vec.size(); i++)
        {
            for (int j = 0; j < all_var_vec.size(); j++)
            {
                if (i == j)
                    continue;
                if (all_var_vec[i].GetName() == all_var_vec[j].GetName())
                {
                    err->emplace_back("Two or more variables have same name: '" +
                                      all_var_vec[i].GetName() +
                                      "'\nSolution: remove duplicated variable or change its name so it wont be the same.");
                }
            }
        }
        // check if variables dont have same name as function

        for (int i = 0; i < all_var_vec.size(); i++)
        {
            if (all_var_vec[i].GetName() == function_name)
            {
                err->emplace_back("One or more local variables have same name as function.'" +
                                  function_name +
                                  "'\nName '"+
                                  function_name + "' is reserved for implicitly declared variable holding function result.\n"
                                  "Solution: change variable name so it wont be same as function name.");
            }
        }
    }

    // TODO parse function body
    std::vector<Lexer::Token> function_body{&tokens[var_begin], &tokens.back()};

    AST::StatementList stmt_list;
    ParseStatementList(err, function_body, &stmt_list);

    AST::Function function;

    function.name = function_name;
    function.var_input = var_input_vec;
    function.var_output = var_output_vec;
    function.var_inout = var_in_out_vec;
    function.var_temp = var_vec;
    function.statements = stmt_list;

    return true;
}

std::vector<AST::VariableDefinition> ParseVarList(
    std::vector<Error> *err,
    const std::vector<Lexer::Token> &tokens)
{

    std::vector<AST::VariableDefinition> variable_list;

    // every single line looks like that:
    //
    //     1=end
    // >>> ;
    // or
    //          1      2    3      end
    //  >>> identifier : data_type ;
    // or
    //          1      2    3       4     5      end
    //  >>> identifier : data_type := expression ;

    int index = 0;
    while (index < tokens.size())
    {
        // find semicolon
        int semicolon_index = FindKeyword(tokens, index, Lexer::TokenType::SEMICOLON);

        if (semicolon_index == -1)
        {
            semicolon_index = tokens.size() - 1;
        }

        std::vector<Lexer::Token> var_decl{&tokens[index], &tokens[semicolon_index] + 1 };
        AST::VariableDefinition variable;

        if (ParseVarDeclaration(err, var_decl, &variable))
        {
            variable_list.emplace_back(variable);
        }

        index = semicolon_index + 1;
    }

    return variable_list;
}

/// @brief
/// @param tokens
/// @param var_begin
/// @param var_end
/// @param var
/// @return True if successfuly converted variable;
/// False if empty expression or error
bool ParseVarDeclaration(
    std::vector<Error> *err,
    const std::vector<Lexer::Token> &tokens,
    AST::VariableDefinition *variable)
{

    if (variable == nullptr)
    {
        throw "XDDD";
    }

    // every single line looks like that:
    //
    //     1=end
    // >>> ;
    // or
    //          1      2    3      end
    //  >>> identifier : data_type ;
    // or
    //          1      2    3       4     5      end
    //  >>> identifier : data_type := expression ;

    // check for empty line
    // >>> ;
    if (tokens[0].type == Lexer::TokenType::SEMICOLON)
    {
        return false; // no error
    }

    // check for:
    // >>> identifier : data_type ;
    // and
    // >>> identifier : data_type := expression ;
    {
        if (tokens[0].type != Lexer::TokenType::IDENTIFIER)
        {
            err->emplace_back("Expected variable name at: " + tokens[0].pos.ToString());
            return false;
        }

        if (tokens[1].type != Lexer::TokenType::COLON)
        {
            err->emplace_back("Expected colon ':' at: " + tokens[1].pos.ToString());
            return false;
        }

        if (tokens[2].type != Lexer::TokenType::IDENTIFIER)
        {
            err->emplace_back("Expected data type at: " + tokens[2].pos.ToString());
            return false;
        }

        if (tokens[3].type == Lexer::TokenType::SEMICOLON)
        {
            (*variable) = AST::VariableDefinition(tokens[0].str, tokens[2].str);
            return true;
        }

        // find Assignment symbol

        if (tokens[3].type != Lexer::TokenType::ASSIGN)
        {
            err->emplace_back("Expected semicolon ';' or assignment operator ':=' at: " + tokens[3].pos.ToString());
            return false;
        }

        if (tokens.back().type != Lexer::TokenType::SEMICOLON)
        {
            err->emplace_back("Missing semicolon ';' at end of expression, at: " + tokens.back().pos.ToString());
            return false;
        }

        // TODO: parse expression
        std::vector<Lexer::Token> assigned_expr{&tokens[4], &tokens.back()};

        (*variable) = AST::VariableDefinition(tokens[0].str, tokens[2].str);
        return true;
    }

    return true;
}

int FindKeyword(
    const std::vector<Lexer::Token> &tokens,
    int begin,
    Lexer::TokenType keyword)
{

    for (int index = begin; index < tokens.size(); index++)
    {
        if (tokens[index].type == keyword)
        {
            return index;
        }
    }

    return -1;
}

int FindKeyword(
    const std::vector<Lexer::Token> &tokens,
    Lexer::TokenType keyword)
{
    return FindKeyword(tokens, 0, keyword);
}
