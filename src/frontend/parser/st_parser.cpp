
#include "st_parser.hpp"
#include <assert.h>

namespace StParser
{

    std::pair<int, int> FindTokenPair(const Lexer::TokenList &tokens, Lexer::TokenType first, Lexer::TokenType second)
    {
        int first_index = -1;
        int second_index = -1;

        for (int index = 0; index < tokens.size(); index++)
        {
            if (tokens[index].type == first)
            {
                first_index = index;
                break;
            }
        }

        if (first_index == -1)
        {
            return {first_index, second_index};
        }

        for (int index = first_index; index < tokens.size(); index++)
        {
            if (tokens[index].type == second)
            {
                first_index = index;
                break;
            }
        }

        return {first_index, second_index};
    }

    int FindToken(const Lexer::TokenList &tokens, int start, Lexer::TokenType type)
    {
        for (int index = start; index < tokens.size(); index++)
        {
            if (tokens[index].type == type)
            {
                return index;
            }
        }
        return -1;
    }

    int FindToken(const Lexer::TokenList &tokens, Lexer::TokenType type)
    {
        return FindToken(tokens, 0, type);
    }

    Lexer::TokenList Split(const Lexer::TokenList &tokens, int first, int second)
    {
        if (first < 0)
        {
            first += tokens.size();
        }

        if (second < 0)
        {
            second += tokens.size();
        }

        assert(IsIndexInBounds(tokens, first));
        assert(IsIndexInBounds(tokens, second));

        return Lexer::TokenList(&tokens[first], &tokens[second] + 1);
    }

    Lexer::TokenList Split(const Lexer::TokenList &tokens, std::pair<int, int> index)
    {
        return Split(tokens, index.first, index.second);
    }

    bool IsTokenTypeAt(Lexer::TokenList &tokens, int index, Lexer::TokenType type)
    {
        if (!IsIndexInBounds(tokens, index))
            return false;

        return tokens[index].type == type;
    }

    int FindTokenAndIgnoreNeasted(const Lexer::TokenList &tokens, Lexer::TokenType searched_token, std::pair<Lexer::TokenType, Lexer::TokenType> nested_ignored)
    {
        return FindTokenAndIgnoreNeasted(tokens, 0, searched_token, nested_ignored);
    }

    int FindTokenAndIgnoreNeasted(const Lexer::TokenList &tokens, int start_index, Lexer::TokenType searched_token, std::pair<Lexer::TokenType, Lexer::TokenType> nested_ignored)
    {
        return FindTokenAndIgnoreNeasted(tokens, start_index, {searched_token}, nested_ignored).first;
    }

    std::pair<int, Lexer::TokenType> FindTokenAndIgnoreNeasted(const Lexer::TokenList &tokens, int start_index, std::initializer_list<Lexer::TokenType> searched_tokens, std::pair<Lexer::TokenType, Lexer::TokenType> nested_ignored)
    {
        int nesting_counter = 0;

        for (int index = start_index; index < tokens.size(); index++)
        {

            if (nesting_counter == 0)
            {

                for (Lexer::TokenType searched_token : searched_tokens)
                {
                    if (tokens[index].type == searched_token)
                    {
                        return {index, searched_token};
                    }
                }
            }

            if (tokens[index].type == nested_ignored.first)
            {
                nesting_counter++;
                continue;
            }

            if (tokens[index].type == nested_ignored.second)
            {
                nesting_counter--;
                continue;
            }
        }

        return {-1, *searched_tokens.begin()};
    }

    bool ExpectToken(const Lexer::TokenList &tokens, int index, Lexer::TokenType type)
    {
        if (index < 0)
        {
            index += tokens.size();
        }

        if (tokens.size() == 0)
        {
            ErrorManager::Create(Error::MissingKeyword(Position(nullptr, 0, 0), type));                                                 // TODO handle special case
            ErrorManager::Create(Error::InternalCompilerError(__FILE__ ":" + std::to_string(__LINE__) + " Empty token list")); // TODO handle special case
            return false;
        }

        if (index < 0)
        {
            ErrorManager::Create(Error::MissingKeyword(tokens[0].pos, type));
            return false;
        }

        if (index > tokens.size())
        {
            ErrorManager::Create(Error::MissingKeyword(tokens[tokens.size()].pos, type));
            return false;
        }

        if (tokens[index].type != type)
        {
            ErrorManager::Create(Error::ExpectedKeyword(tokens[index].pos, type));
            return false;
        }

        return true;
    }

    AST::PouList Parse(const Lexer::TokenList tokens, bool is_extern)
    {

        AST::PouList pou_list;

        int token_index = 0;
        while (token_index < tokens.size())
        {
            int end_index = -1;
            AST::PouPtr pou;

            // find pair FUNCTION - END_FUNCTION
            if (tokens[token_index].type == Lexer::TokenType::FUNCTION)
            {
                end_index = FindToken(tokens, token_index, Lexer::TokenType::END_FUNCTION);
                pou = ParseFunction(Split(tokens, token_index, end_index), is_extern);
                pou_list.push_back(pou);
            }

            // find pair FUNCTION_BLOCK - END_FUNCTION_BLOCK
            else if (tokens[token_index].type == Lexer::TokenType::FUNCTION_BLOCK)
            {
                end_index = FindToken(tokens, token_index, Lexer::TokenType::END_FUNCTION_BLOCK);
                pou = ParseFunctionBlock(Split(tokens, token_index, end_index), is_extern);
                pou_list.push_back(pou);
            }

            // find pair PROGRAM - END_PROGRAM
            else if (tokens[token_index].type == Lexer::TokenType::PROGRAM)
            {
                end_index = FindToken(tokens, token_index, Lexer::TokenType::END_PROGRAM);
                pou = ParseProgram(Split(tokens, token_index, end_index), is_extern);
                pou_list.push_back(pou);
            }

            // if previous keywords not found, then throw unexpected token error
            else
            {
                Position pos = tokens[token_index].pos;
                Lexer::TokenType type = tokens[token_index].type;
                ErrorManager::Create(Error::UnexpectedTokenError(pos, type));
            }

            if(end_index == -1)
            {
                break;
            }
            token_index = end_index + 1;
        }
        return pou_list;
    }

    AST::PouPtr ParseFunction(Lexer::TokenList tokens, bool is_extern)
    {
        AST::Function function(is_extern);

        if (!ExpectToken(tokens, 0, Lexer::TokenType::FUNCTION))
            return AST::MakePou(function);

        if (!ExpectToken(tokens, 1, Lexer::TokenType::IDENTIFIER))
            return AST::MakePou(function);

        if (!ExpectToken(tokens, -1, Lexer::TokenType::END_FUNCTION))
            return AST::MakePou(function);

        std::string pou_name = tokens[1].str;
        std::string return_type = ""; // empty string means that function does not have return type

        int body_start_index = 2;

        function.name = pou_name;

        // check for return value;
        if (IsTokenTypeAt(tokens, 2, Lexer::TokenType::COLON))
        {
            if (!ExpectToken(tokens, 2, Lexer::TokenType::COLON))
                return AST::MakePou(function);

            if (!ExpectToken(tokens, 3, Lexer::TokenType::IDENTIFIER))
                return AST::MakePou(function);

            return_type = tokens[3].str;
            body_start_index = 4;
            function.result = std::make_shared<AST::Variable>(pou_name, return_type);
        }

        PouBody body = ParsePouBody(Split(tokens, body_start_index, -2));
        function.statement_list = body.stmt_list;
        function.var = body.vars.var;
        function.var_input = body.vars.input;
        function.var_output = body.vars.output;
        function.var_in_out = body.vars.input_output;
        return AST::MakePou(function);
    }

    AST::PouPtr ParseFunctionBlock(Lexer::TokenList tokens, bool is_extern)
    {
        AST::FunctionBlock function_block(is_extern);

        if (!ExpectToken(tokens, 0, Lexer::TokenType::FUNCTION_BLOCK))
            return AST::MakePou(function_block);

        if (!ExpectToken(tokens, 1, Lexer::TokenType::IDENTIFIER))
            return AST::MakePou(function_block);

        if (!ExpectToken(tokens, -1, Lexer::TokenType::END_FUNCTION_BLOCK))
            return AST::MakePou(function_block);

        std::string pou_name = tokens[1].str;
        std::string return_type = ""; // empty string means that function does not have return type

        function_block.name = pou_name;

        int body_start_index = 2;

        // check for return value;
        if (IsTokenTypeAt(tokens, 2, Lexer::TokenType::COLON))
        {
            if (!ExpectToken(tokens, 2, Lexer::TokenType::COLON))
                return AST::MakePou(function_block);

            if (!ExpectToken(tokens, 3, Lexer::TokenType::IDENTIFIER))
                return AST::MakePou(function_block);

            return_type = tokens[3].str;
            body_start_index = 4;

            return_type = tokens[3].str;
            body_start_index = 4;
            function_block.result = std::make_shared<AST::Variable>(pou_name, return_type);
        }

        PouBody body = ParsePouBody(Split(tokens, body_start_index, -2));
        function_block.statement_list = body.stmt_list;
        function_block.var = body.vars.var;
        function_block.var_input = body.vars.input;
        function_block.var_output = body.vars.output;
        function_block.var_in_out = body.vars.input_output;
        return AST::MakePou(function_block);
    }

    AST::PouPtr ParseProgram(Lexer::TokenList tokens, bool is_extern)
    {
        AST::Program program(is_extern);

        if (!ExpectToken(tokens, 0, Lexer::TokenType::PROGRAM))
            return AST::MakePou(program);

        if (!ExpectToken(tokens, 1, Lexer::TokenType::IDENTIFIER))
            return AST::MakePou(program);

        if (!ExpectToken(tokens, -1, Lexer::TokenType::END_PROGRAM))
            return AST::MakePou(program);

        std::string pou_name = tokens[1].str;
        program.name = pou_name;

        PouBody body = ParsePouBody(Split(tokens, 2, -2));
        program.statement_list = body.stmt_list;
        program.var = body.vars.var;
        program.var_input = body.vars.input;
        program.var_output = body.vars.output;
        program.var_in_out = body.vars.input_output;
        return AST::MakePou(program);
    }

    PouBody ParsePouBody(Lexer::TokenList tokens)
    {
        PouBody body;
        // find and parse VAR blocks
        int last_var_index = 0;
        body.vars = ParseAllVars(tokens, &last_var_index);

        // parse statement list
        Lexer::TokenList statemens_tokens = Split(tokens, last_var_index, -1);
        body.stmt_list = ParseStatementList(statemens_tokens);

        return body;
    }

    AST::StmtList ParseStatementList(Lexer::TokenList tokens)
    {
        AST::StmtList statement_list;

        int token_index = 0;
        while (token_index < tokens.size())
        {
            int end_index = token_index;
            AST::StmtPtr stmt;

            // IF statement
            if (tokens[token_index].type == Lexer::TokenType::IF)
            {
                end_index = FindTokenAndIgnoreNeasted(
                    tokens, token_index, Lexer::TokenType::SEMICOLON,
                    {Lexer::TokenType::IF, Lexer::TokenType::END_IF});

                stmt = ParseIfStatement(Split(tokens, token_index, end_index));
            }

            // WHILE statement
            else if (tokens[token_index].type == Lexer::TokenType::WHILE)
            {
                end_index = FindTokenAndIgnoreNeasted(
                    tokens, token_index, Lexer::TokenType::SEMICOLON,
                    {Lexer::TokenType::WHILE, Lexer::TokenType::END_WHILE});

                stmt = ParseWhileStatement(Split(tokens, token_index, end_index));
            }

            // FOR statement
            else if (tokens[token_index].type == Lexer::TokenType::FOR)
            {
                end_index = FindTokenAndIgnoreNeasted(
                    tokens, token_index, Lexer::TokenType::SEMICOLON,
                    {Lexer::TokenType::FOR, Lexer::TokenType::END_FOR});

                stmt = ParseWhileStatement(Split(tokens, token_index, end_index));
            }

            // REPEAT statement
            else if (tokens[token_index].type == Lexer::TokenType::REPEAT)
            {
                end_index = FindTokenAndIgnoreNeasted(
                    tokens, token_index, Lexer::TokenType::SEMICOLON,
                    {Lexer::TokenType::REPEAT, Lexer::TokenType::END_REPEAT});

                stmt = ParseWhileStatement(Split(tokens, token_index, end_index));
            }
            else
            {
                end_index = FindToken(tokens, token_index, Lexer::TokenType::SEMICOLON);
                stmt = ParseStatement(Split(tokens, token_index, end_index));

                // TODO parse assignment expression or function call
            }
            if(end_index == -1)
            {
                end_index = tokens.size();
            }
            statement_list.push_back(stmt);
            token_index = end_index + 1;
        }

        return statement_list;
    }

    // three types of statement
    // 1) empty statement `;`
    // 2) assignment statement `A := B;`
    // 2) unassigned expression (for example: function call) `A;`
    AST::StmtPtr ParseStatement(Lexer::TokenList tokens)
    {
        if (!ExpectToken(tokens, -1, Lexer::TokenType::SEMICOLON))
            return AST::MakeStmt(AST::EmptyStatement());

        if (tokens.size() == 1)
        {
            return AST::MakeStmt(AST::EmptyStatement()); // empty statement. DO NOT EMIT code
        }

        int assign_operator_index = FindToken(tokens, Lexer::TokenType::ASSIGN);

        if (assign_operator_index == -1)
        {
            Lexer::TokenList expr_tokens = Split(tokens, 0, -2);
            AST::ExprPtr expr = Expression::Parse(expr_tokens);
            return AST::MakeStmt(AST::NonAsssingingStatement(expr));
        }
        else
        {
            Lexer::TokenList left_expr_tokens = Split(tokens, 0, assign_operator_index - 1);
            Lexer::TokenList right_expr_tokens = Split(tokens, assign_operator_index + 1, -2);

            AST::ExprPtr left_expr = Expression::Parse(left_expr_tokens);
            AST::ExprPtr right_expr = Expression::Parse(right_expr_tokens);

            return AST::MakeStmt(AST::AssignmentStatement(left_expr, right_expr));
        }
    }

    // FOR ... TO ... BY ... DO
    // ...
    // END_FOR;
    AST::StmtPtr ParseForStatement(Lexer::TokenList tokens)
    {
        if (!ExpectToken(tokens, 0, Lexer::TokenType::FOR))
            return AST::MakeStmt(AST::EmptyStatement());
        if (!ExpectToken(tokens, -2, Lexer::TokenType::END_FOR))
            return AST::MakeStmt(AST::EmptyStatement());
        if (!ExpectToken(tokens, -1, Lexer::TokenType::SEMICOLON))
            return AST::MakeStmt(AST::EmptyStatement());

        int to_keyword_pos = FindToken(tokens, 1, Lexer::TokenType::TO);
        int by_keyword_pos = FindToken(tokens, to_keyword_pos, Lexer::TokenType::BY);
        int do_keyword_pos = FindToken(tokens, by_keyword_pos, Lexer::TokenType::DO);

        if (to_keyword_pos == -1)
        {
            ErrorManager::Create(Error::MissingKeywordAfter(tokens[0].pos, tokens[0].type, Lexer::TokenType::TO));
            return AST::MakeStmt(AST::EmptyStatement());
        }

        if (by_keyword_pos == -1)
        {
            ErrorManager::Create(Error::MissingKeywordAfter(tokens[0].pos, tokens[0].type, Lexer::TokenType::BY));
            return AST::MakeStmt(AST::EmptyStatement());
        }

        if (do_keyword_pos == -1)
        {
            ErrorManager::Create(Error::MissingKeywordAfter(tokens[0].pos, tokens[0].type, Lexer::TokenType::DO));
            return AST::MakeStmt(AST::EmptyStatement());
        }

        Lexer::TokenList control_var_init_tokens = Split(tokens, 1, to_keyword_pos - 1);                 // FOR ... TO
        Lexer::TokenList final_value_tokens = Split(tokens, to_keyword_pos + 1, by_keyword_pos - 1);     // TO ... BY
        Lexer::TokenList increment_value_tokens = Split(tokens, by_keyword_pos + 1, do_keyword_pos - 1); // BY ... DO
        Lexer::TokenList statement_list_tokens = Split(tokens, do_keyword_pos + 1, -2);                  // DO ... END_FOR;

        // todo parse condition
        // todo parse statement_list
        AST::StmtList statement_list = ParseStatementList(statement_list_tokens);

        // TODO
        return AST::MakeStmt(AST::EmptyStatement());
    }

    // WHILE ... DO
    // ...
    // END_WHILE;
    AST::StmtPtr ParseWhileStatement(Lexer::TokenList tokens)
    {
        if (!ExpectToken(tokens, 0, Lexer::TokenType::WHILE))
            return AST::MakeStmt(AST::EmptyStatement());
        if (!ExpectToken(tokens, -2, Lexer::TokenType::END_WHILE))
            return AST::MakeStmt(AST::EmptyStatement());
        if (!ExpectToken(tokens, -1, Lexer::TokenType::SEMICOLON))
            return AST::MakeStmt(AST::EmptyStatement());

        int do_keyword_pos = FindToken(tokens, Lexer::TokenType::DO);
        if (do_keyword_pos == -1)
        {
            ErrorManager::Create(Error::MissingKeywordAfter(tokens[0].pos, tokens[0].type, Lexer::TokenType::DO));
            return AST::MakeStmt(AST::EmptyStatement());
        }

        Lexer::TokenList condition_tokens = Split(tokens, 1, do_keyword_pos - 1);
        Lexer::TokenList statement_list_tokens = Split(tokens, do_keyword_pos + 1, -3);

        AST::ExprPtr condition = Expression::Parse(condition_tokens);
        AST::StmtList statemen_list = ParseStatementList(statement_list_tokens);

        return AST::MakeStmt(AST::WhileStatement(condition, statemen_list));
    }

    // REPEAT
    // ...
    // UNTIL ...
    // END_WHILE;
    AST::StmtPtr ParseRepeatStatement(Lexer::TokenList tokens)
    {
        if (!ExpectToken(tokens, 0, Lexer::TokenType::REPEAT))
            return AST::MakeStmt(AST::EmptyStatement());
        if (!ExpectToken(tokens, -2, Lexer::TokenType::END_REPEAT))
            return AST::MakeStmt(AST::EmptyStatement());
        if (!ExpectToken(tokens, -1, Lexer::TokenType::SEMICOLON))
            return AST::MakeStmt(AST::EmptyStatement());

        int until_keyword_pos = FindTokenAndIgnoreNeasted(
            tokens, 1, Lexer::TokenType::UNTIL,
            {Lexer::TokenType::REPEAT, Lexer::TokenType::END_REPEAT});

        if (until_keyword_pos == -1)
        {
            ErrorManager::Create(Error::MissingKeywordAfter(tokens[0].pos, tokens[0].type, Lexer::TokenType::UNTIL));
            return AST::MakeStmt(AST::EmptyStatement());
        }

        Lexer::TokenList statement_list_tokens = Split(tokens, 1, until_keyword_pos - 1);
        Lexer::TokenList condition_tokens = Split(tokens, until_keyword_pos + 1, -3);

        // todo parse condition
        // todo parse statement_list
        AST::StmtList stmt_list = ParseStatementList(statement_list_tokens);
        return AST::MakeStmt(AST::EmptyStatement());
    }

    // TODO: finish this (or refactor)
    // simplified version of IF
    // IF .. THEN
    //     ...
    // END_IF;
    AST::StmtPtr ParseIfStatement(Lexer::TokenList tokens)
    {
        if (!ExpectToken(tokens, 0, Lexer::TokenType::IF))
            return AST::MakeStmt(AST::EmptyStatement());

        if (!ExpectToken(tokens, -2, Lexer::TokenType::END_IF))
            return AST::MakeStmt(AST::EmptyStatement());

        if (!ExpectToken(tokens, -1, Lexer::TokenType::SEMICOLON))
            return AST::MakeStmt(AST::EmptyStatement());

        int then_keyword_pos = FindTokenAndIgnoreNeasted(
            tokens, 1, Lexer::TokenType::THEN,
            {Lexer::TokenType::IF, Lexer::TokenType::END_IF});

        if (then_keyword_pos == -1)
        {
            ErrorManager::Create(Error::MissingKeywordAfter(tokens[0].pos, tokens[0].type, Lexer::TokenType::THEN));
            return AST::MakeStmt(AST::EmptyStatement());
        }

        Lexer::TokenList condition_tokens = Split(tokens, 1, then_keyword_pos - 1);
        Lexer::TokenList statement_list_tokens = Split(tokens, then_keyword_pos + 1, -3);

        // todo parse condition
        // todo parse statement_list
        AST::ExprPtr condition = Expression::Parse(condition_tokens);
        AST::StmtList statement_list = ParseStatementList(statement_list_tokens);
        return AST::MakeStmt(AST::IfStatement(condition, statement_list));
    }

    AllVars ParseAllVars(Lexer::TokenList tokens, int *last_position)
    {
        AllVars vars;

        // first find VAR .. END_VAR blocks
        int token_index = 0;
        while (token_index < tokens.size())
        {
            int end_index = -1;

            // find pair VAR .. END_VAR
            if (tokens[token_index].type == Lexer::TokenType::VAR)
            {
                end_index = FindToken(tokens, token_index, Lexer::TokenType::END_VAR);
                vars.var = ParseVar(Split(tokens, token_index, end_index));
            }

            // find pair VAR_INPUT .. END_VAR
            else if (tokens[token_index].type == Lexer::TokenType::VAR_INPUT)
            {
                end_index = FindToken(tokens, token_index, Lexer::TokenType::END_VAR);
                vars.input = ParseVarInput(Split(tokens, token_index, end_index));
            }

            // find pair VAR_IN_OUT .. END_VAR
            else if (tokens[token_index].type == Lexer::TokenType::VAR_IN_OUT)
            {
                end_index = FindToken(tokens, token_index, Lexer::TokenType::END_VAR);
                vars.input_output = ParseVarInOut(Split(tokens, token_index, end_index));
            }

            // find pair VAR_OUTPUT .. END_VAR
            else if (tokens[token_index].type == Lexer::TokenType::VAR_OUTPUT)
            {
                end_index = FindToken(tokens, token_index, Lexer::TokenType::END_VAR);
                vars.output = ParseVarOutput(Split(tokens, token_index, end_index));
            }

            // if previous keywords not found, then  return result and last position
            else
            {
                *last_position = token_index;
                return vars;
            }

            token_index = end_index + 1;
        }

        return vars;
    }

    AST::VarList ParseVar(Lexer::TokenList tokens)
    {
        if (!ExpectToken(tokens, 0, Lexer::TokenType::VAR))
            return {};

        if (!ExpectToken(tokens, -1, Lexer::TokenType::END_VAR))
            return {};

        return ParseVarBody(Split(tokens, 1, -2));
    }

    AST::VarList ParseVarInput(Lexer::TokenList tokens)
    {
        if (!ExpectToken(tokens, 0, Lexer::TokenType::VAR_INPUT))
            return {};

        if (!ExpectToken(tokens, -1, Lexer::TokenType::END_VAR))
            return {};

        return ParseVarBody(Split(tokens, 1, -2));
    }

    AST::VarList ParseVarInOut(Lexer::TokenList tokens)
    {
        if (!ExpectToken(tokens, 0, Lexer::TokenType::VAR_IN_OUT))
            return {};

        if (!ExpectToken(tokens, -1, Lexer::TokenType::END_VAR))
            return {};

        return ParseVarBody(Split(tokens, 1, -2));
    }

    AST::VarList ParseVarOutput(Lexer::TokenList tokens)
    {
        if (!ExpectToken(tokens, 0, Lexer::TokenType::VAR_OUTPUT))
            return {};

        if (!ExpectToken(tokens, -1, Lexer::TokenType::END_VAR))
            return {};

        return ParseVarBody(Split(tokens, 1, -2));
    }

    AST::VarList ParseVarBody(Lexer::TokenList tokens)
    {
        AST::VarList variables;

        int index = 0;
        while (index < tokens.size())
        {
            // find semicolon separating variables
            int end_index = FindToken(tokens, index, Lexer::TokenType::SEMICOLON);
            AST::Variable variable = ParseVariableDeclaration(Split(tokens, index, end_index));
            variables.push_back(variable);

            index = end_index + 1;
        }

        return variables;
    }

    AST::Variable ParseVariableDeclaration(Lexer::TokenList tokens)
    {
        if (!ExpectToken(tokens, 0, Lexer::TokenType::IDENTIFIER))
            return AST::Variable();

        if (!ExpectToken(tokens, 1, Lexer::TokenType::COLON))
            return AST::Variable();

        if (!ExpectToken(tokens, 2, Lexer::TokenType::IDENTIFIER))
            return AST::Variable();

        if (!ExpectToken(tokens, -1, Lexer::TokenType::SEMICOLON))
            return AST::Variable();

        std::string variable_name = tokens[0].str;
        std::string data_type = tokens[2].str;

        if (tokens.size() == 4)
        {
            return AST::Variable(variable_name, data_type);
        }

        if (!ExpectToken(tokens, 3, Lexer::TokenType::ASSIGN))
            return AST::Variable();

        Lexer::TokenList init_expression_tokens = Split(tokens, 4, -2);
        AST::ExprPtr initial_value = Expression::Parse(init_expression_tokens);

        return AST::Variable(variable_name, data_type, initial_value);
    }

}
