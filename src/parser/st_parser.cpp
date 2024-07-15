
#include "st_parser.hpp"

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

    bool ExpectToken(Error::ErrorList_t &err, const Lexer::TokenList &tokens, int index, Lexer::TokenType type)
    {
        if (index < 0)
        {
            index += tokens.size();
        }

        if (tokens.size() == 0)
        {
            Error::PushError(err, Error::MissingKeyword(Position(0, 0), type));                                                 // TODO handle special case
            Error::PushError(err, Error::InternalCompilerError(__FILE__ ":" + std::to_string(__LINE__) + " Empty token list")); // TODO handle special case
            return false;
        }

        if (index < 0)
        {
            Error::PushError(err, Error::MissingKeyword(tokens[0].pos, type));
            return false;
        }

        if (index > tokens.size())
        {
            Error::PushError(err, Error::MissingKeyword(tokens[tokens.size()].pos, type));
            return false;
        }

        if (tokens[index].type != type)
        {
            Error::PushError(err, Error::ExpectedKeyword(tokens[index].pos, type));
            return false;
        }

        return true;
    }

    void Parse(Error::ErrorList_t &err, const Lexer::TokenList tokens)
    {

        int token_index = 0;
        while (token_index < tokens.size())
        {
            int end_index = -1;

            // find pair FUNCTION - END_FUNCTION
            if (tokens[token_index].type == Lexer::TokenType::FUNCTION)
            {
                end_index = FindToken(tokens, token_index, Lexer::TokenType::END_FUNCTION);
                ParseFunction(err, Split(tokens, token_index, end_index));
            }

            // find pair FUNCTION_BLOCK - END_FUNCTION_BLOCK
            else if (tokens[token_index].type == Lexer::TokenType::FUNCTION_BLOCK)
            {
                end_index = FindToken(tokens, token_index, Lexer::TokenType::END_FUNCTION_BLOCK);
                ParseFunctionBlock(err, Split(tokens, token_index, end_index));
            }

            // find pair PROGRAM - END_PROGRAM
            else if (tokens[token_index].type == Lexer::TokenType::PROGRAM)
            {
                end_index = FindToken(tokens, token_index, Lexer::TokenType::END_PROGRAM);
                ParseProgram(err, Split(tokens, token_index, end_index));
            }

            // if previous keywords not found, then throw unexpected token error
            else
            {
                Position pos = tokens[token_index].pos;
                Lexer::TokenType type = tokens[token_index].type;
                Error::PushError(err, Error::UnexpectedTokenError(pos, type));
            }

            token_index = end_index + 1;
        }
    }

    void ParseFunction(Error::ErrorList_t &err, Lexer::TokenList tokens)
    {
        if (!ExpectToken(err, tokens, 0, Lexer::TokenType::FUNCTION))
            return;

        if (!ExpectToken(err, tokens, 1, Lexer::TokenType::IDENTIFIER))
            return;

        if (!ExpectToken(err, tokens, -1, Lexer::TokenType::END_FUNCTION))
            return;

        std::string pou_name = tokens[1].str;
        std::string return_type = ""; // empty string means that function does not have return type

        int body_start_index = 2;

        // check for return value;
        if (IsTokenTypeAt(tokens, 2, Lexer::TokenType::COLON))
        {
            if (!ExpectToken(err, tokens, 2, Lexer::TokenType::COLON))
                return;

            if (!ExpectToken(err, tokens, 3, Lexer::TokenType::IDENTIFIER))
                return;

            return_type = tokens[3].str;
            body_start_index = 4;
        }

        ParsePouBody(err, Split(tokens, body_start_index, -2));
    }

    void ParseFunctionBlock(Error::ErrorList_t &err, Lexer::TokenList tokens)
    {
        if (!ExpectToken(err, tokens, 0, Lexer::TokenType::FUNCTION_BLOCK))
            return;

        if (!ExpectToken(err, tokens, 1, Lexer::TokenType::IDENTIFIER))
            return;

        if (!ExpectToken(err, tokens, -1, Lexer::TokenType::END_FUNCTION))
            return;

        std::string pou_name = tokens[1].str;

        ParsePouBody(err, Split(tokens, 2, -2));
    }

    void ParseProgram(Error::ErrorList_t &err, Lexer::TokenList tokens)
    {
        if (!ExpectToken(err, tokens, 0, Lexer::TokenType::PROGRAM))
            return;

        if (!ExpectToken(err, tokens, 1, Lexer::TokenType::IDENTIFIER))
            return;

        if (!ExpectToken(err, tokens, -1, Lexer::TokenType::END_FUNCTION))
            return;

        std::string pou_name = tokens[1].str;

        ParsePouBody(err, Split(tokens, 2, -2));
    }

    void ParsePouBody(Error::ErrorList_t &err, Lexer::TokenList tokens)
    {
        // find and parse VAR blocks
        int last_var_index = 0;
        ParseAllVars(err, tokens, &last_var_index);

        // parse statement list
        Lexer::TokenList statemens_tokens = Split(tokens, last_var_index, -1);
        ParseStatementList(err, statemens_tokens);
    }

    void ParseStatementList(Error::ErrorList_t &err, Lexer::TokenList tokens)
    {
        int token_index = 0;
        while (token_index < tokens.size())
        {
            int end_index = token_index;

            if (tokens[token_index].type == Lexer::TokenType::IF)
            {
                int end_index = FindTokenAndIgnoreNeasted(tokens, token_index + 1, Lexer::TokenType::END_IF, {Lexer::TokenType::IF, Lexer::TokenType::END_IF});
                ParseIfStatement(err, Split(tokens, token_index, end_index));
            }
            else
            {
                // TODO parse assignment expression
            }
            token_index = end_index + 1;
        }
    }

    // IF .. THEN
    //     ...
    // - ELSIF .. THEN
    //     ...
    // - ELSIF .. THEN
    //     ...
    // - ELSIF .. THEN
    //     ...
    // - ELSIF .. THEN
    //     ...
    // - ELSE
    //     ...
    // END_IF
    void ParseIfStatement(Error::ErrorList_t &err, Lexer::TokenList tokens)
    {
        if (!ExpectToken(err, tokens, 0, Lexer::TokenType::IF))
            return;

        if (!ExpectToken(err, tokens, -1, Lexer::TokenType::END_IF))
            return;

        const std::pair<Lexer::TokenType, Lexer::TokenType> ignore_neasted =
            {Lexer::TokenType::IF, Lexer::TokenType::END_IF};

        std::vector<Lexer::TokenList> condition_tokens_vec;
        std::vector<Lexer::TokenList> statement_list_tokens_vec;
        std::vector<Lexer::TokenList> else_statement_list_tokens_vec;

        bool found_else_keyword = false;
        int index = 0; // index of IF or ELSIF
        int iter = 0;

        while (index < tokens.size())
        {
            int then_index = FindTokenAndIgnoreNeasted(tokens, index + 1, Lexer::TokenType::THEN, ignore_neasted);
            if (then_index == -1)
            {
                Error::PushError(err, Error::MissingKeyword(tokens[index].pos, Lexer::TokenType::THEN));
                return;
            }

            Lexer::TokenList condition_tokens = Split(tokens, index + 1, then_index - 1);

            std::pair<int, Lexer::TokenType> search_result =
                FindTokenAndIgnoreNeasted(tokens, then_index, {Lexer::TokenType::ELSIF, Lexer::TokenType::ELSE, Lexer::TokenType::END_IF}, ignore_neasted);

            int end_index = search_result.first;
            Lexer::TokenType end_keyword = search_result.second;

            Lexer::TokenList statement_list_tokens = Split(tokens, then_index + 1, end_index - 1);

            condition_tokens_vec.push_back(condition_tokens);
            statement_list_tokens_vec.push_back(statement_list_tokens);

            if (end_index == -1)
            {
                Error::PushError(err, Error::MissingKeyword(tokens[index].pos, Lexer::TokenType::END_IF));
                return;
            }

            if (end_keyword == Lexer::TokenType::END_IF)
            {
                if (end_index == (tokens.size() - 1))
                {
                    break;
                }
                else
                {
                    Error::PushError(err, Error::MissingKeyword(tokens[index].pos, Lexer::TokenType::END_IF));
                    return;
                }
            }
        }

        


    }

    void ParseAllVars(Error::ErrorList_t &err, Lexer::TokenList tokens, int *last_position)
    {

        // first find VAR .. END_VAR blocks
        int token_index = 0;
        while (token_index < tokens.size())
        {
            int end_index = -1;

            // find pair VAR .. END_VAR
            if (tokens[token_index].type == Lexer::TokenType::VAR)
            {
                end_index = FindToken(tokens, token_index, Lexer::TokenType::END_VAR);
                ParseVar(err, Split(tokens, token_index, end_index));
            }

            // find pair VAR_INPUT .. END_VAR
            else if (tokens[token_index].type == Lexer::TokenType::VAR_INPUT)
            {
                end_index = FindToken(tokens, token_index, Lexer::TokenType::END_VAR);
                ParseVarInput(err, Split(tokens, token_index, end_index));
            }

            // find pair VAR_IN_OUT .. END_VAR
            else if (tokens[token_index].type == Lexer::TokenType::VAR_IN_OUT)
            {
                end_index = FindToken(tokens, token_index, Lexer::TokenType::END_VAR);
                ParseVarInOut(err, Split(tokens, token_index, end_index));
            }

            // find pair VAR_OUTPUT .. END_VAR
            else if (tokens[token_index].type == Lexer::TokenType::VAR_OUTPUT)
            {
                end_index = FindToken(tokens, token_index, Lexer::TokenType::END_VAR);
                ParseVarOutput(err, Split(tokens, token_index, end_index));
            }

            // if previous keywords not found, then  return result and last position
            else
            {
                *last_position = end_index + 1;
                return;
            }

            token_index = end_index + 1;
        }
    }

    void ParseVar(Error::ErrorList_t &err, Lexer::TokenList tokens)
    {
        if (!ExpectToken(err, tokens, 0, Lexer::TokenType::VAR))
            return;

        if (!ExpectToken(err, tokens, -1, Lexer::TokenType::END_VAR))
            return;

        ParseVarBody(err, Split(tokens, 1, -2));
    }

    void ParseVarInput(Error::ErrorList_t &err, Lexer::TokenList tokens)
    {
        if (!ExpectToken(err, tokens, 0, Lexer::TokenType::VAR_INPUT))
            return;

        if (!ExpectToken(err, tokens, -1, Lexer::TokenType::END_VAR))
            return;

        ParseVarBody(err, Split(tokens, 1, -2));
    }

    void ParseVarInOut(Error::ErrorList_t &err, Lexer::TokenList tokens)
    {
        if (!ExpectToken(err, tokens, 0, Lexer::TokenType::VAR_IN_OUT))
            return;

        if (!ExpectToken(err, tokens, -1, Lexer::TokenType::END_VAR))
            return;

        ParseVarBody(err, Split(tokens, 1, -2));
    }

    void ParseVarOutput(Error::ErrorList_t &err, Lexer::TokenList tokens)
    {
        if (!ExpectToken(err, tokens, 0, Lexer::TokenType::VAR_OUTPUT))
            return;

        if (!ExpectToken(err, tokens, -1, Lexer::TokenType::END_VAR))
            return;

        ParseVarBody(err, Split(tokens, 1, -2));
    }

    void ParseVarBody(Error::ErrorList_t &err, Lexer::TokenList tokens)
    {
        int index = 0;
        while (index < tokens.size())
        {
            // find semicolon separating variables
            int end_index = FindToken(tokens, index, Lexer::TokenType::SEMICOLON);
            ParseVariableDeclaration(err, Split(tokens, index, end_index));

            index = end_index + 1;
        }
    }

    void ParseVariableDeclaration(Error::ErrorList_t &err, Lexer::TokenList tokens)
    {
        if (!ExpectToken(err, tokens, 0, Lexer::TokenType::IDENTIFIER))
            return;

        if (!ExpectToken(err, tokens, 1, Lexer::TokenType::COLON))
            return;

        if (!ExpectToken(err, tokens, 2, Lexer::TokenType::IDENTIFIER))
            return;

        if (!ExpectToken(err, tokens, -1, Lexer::TokenType::SEMICOLON))
            return;

        std::string variable_name = tokens[0].str;
        std::string data_type = tokens[2].str;

        if (tokens.size() == 4)
        {
            return;
        }

        if (!ExpectToken(err, tokens, 3, Lexer::TokenType::ASSIGN))
            return;

        Lexer::TokenList init_expression_tokens = Split(tokens, 4, -2);
    }

}
