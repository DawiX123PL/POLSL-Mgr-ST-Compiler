#include "st_lexer.hpp"
#include "../error.hpp"

#include <string>
#include <vector>
#include <array>
#include <cctype>
#include <cstring>
#include <iostream>

namespace Lexer
{

    struct StringAndPos
    {
        std::string str;
        Position pos;
        StringAndPos(std::string _str, Position _pos) : str(_str), pos(_pos){};
    };

    // **********************************************************************************************************************************************
    // Declarations
    bool IsSubstrAtPos(const std::string &code, int pos, char *sub_str);
    void SplitToSubstrings(Error::ErrorList_t &err, const std::string &_code, std::vector<StringAndPos> *tokens_str);
    void SplitConsecutiveOperators(const std::string &code, std::vector<std::string> *oper_list);
    bool TryCategoriseKeywordToken(std::string str, Token *token);
    bool TryCategoriseNumericLiterals(std::string str, Token *token);

    bool IsIdentifierChar(char c);
    bool IsNumericChar(char c);
    bool IsWhite(char c);
    bool IsOperatorChar(char c);

    // **********************************************************************************************************************************************
    // Definitions

    std::vector<TokenList> TokenizeFiles(Error::ErrorList_t &err, const std::vector<File> files)
    {

        std::vector<TokenList> token_list;

        for (int i = 0; i < files.size(); i++)
        {
            token_list.push_back({});
            token_list.back() = Tokenize(err, files[i].content);
        }

        return token_list;
    }

    TokenList Tokenize(Error::ErrorList_t &err, const std::string &code)
    {

        std::vector<StringAndPos> tokens_str;

        SplitToSubstrings(err, code, &tokens_str);

        TokenList token_list;
        token_list.resize(tokens_str.size());

        // categorise tokens
        for (int i = 0; i < tokens_str.size(); i++)
        {
            std::string str = tokens_str[i].str;
            Token *token = &token_list[i];

            if (TryCategoriseKeywordToken(str, token))
            {
                continue;
            }

            if (TryCategoriseNumericLiterals(str, token))
            {
                continue;
            }

            token->type = TokenType::IDENTIFIER;
        }

        // copy position and string from code to new tokens
        for (int i = 0; i < tokens_str.size(); i++)
        {
            token_list[i].str = tokens_str[i].str;
            token_list[i].pos = tokens_str[i].pos;
        }

        return token_list;
    }

    static bool TryCategoriseKeywordToken(std::string str, Token *token)
    {
        constexpr int keywords_list_size = sizeof(keywords_list) / sizeof(keywords_list[0]);
        for (int i = 0; i < keywords_list_size; i++)
        {

            const char *keyword = keywords_list[i].first;

            if (str == keyword)
            {
                token->type = keywords_list[i].second;
                token->str = keyword;
                return true;
            }
        }

        return false;
    }

    static bool TryCategoriseNumericLiterals(std::string str, Token *token)
    {
        // true if first char is numeric
        if (IsNumericChar(str[0]))
        {
            token->type = TokenType::NUMERIC_LITERAL;
            return true;
        }

        // true if contains # symbol
        for (int i = 0; i < str.size(); i++)
        {
            if (str[i] == '#')
            {
                token->type = TokenType::NUMERIC_LITERAL;
                return true;
            }
        }

        return false;
    }

    // TODO comments
    static void SplitToSubstrings(Error::ErrorList_t &err, const std::string &_code, std::vector<StringAndPos> *tokens_str)
    {

        const std::string &code = _code + ' ';

        bool is_numeric = false;

        unsigned char prev = ' ';
        unsigned char curr = ' ';
        unsigned char first = ' ';

        int begining_index = 0;

        Position begining_pos = Position(1, 0);
        Position current_pos = Position(1, 0);

        for (int current_index = 0; current_index < code.size(); current_index++)
        {
            current_pos.col++;

            prev = curr;
            curr = code[current_index];
            first = code[begining_index];

            if (curr == '\n')
            {
                current_pos.col = 0;
                current_pos.line++;
            }

            if (IsNumericChar(first) || curr == '#')
            {
                is_numeric = true;
            }

            //////////////////////////////////////////////////////////////////////

            if (IsIdentifierChar(first) && IsIdentifierChar(curr))
            {
                // do nothing - skip
                continue;
            }
            if (IsWhite(first) && IsWhite(curr))
            {
                // do nothing - skip
                continue;
            }

            if (IsOperatorChar(first) && IsOperatorChar(curr))
            {
                // do nothing - skip
                continue;
            }

            if ((prev == '#') && ((curr == '+') || (curr == '-')))
            {
                // do nothing - skip
                continue;
            }

            if (is_numeric && (curr == '.'))
            {
                // do nothing - skip
                continue;
            }

            if (is_numeric && ((prev == 'e') || (prev == 'E')) && ((curr == '+') || (curr == '-')))
            {
                // do nothing - skip
                continue;
            }

            //////////////////////////////////////////////////////////////////////

            if (IsWhite(first) && IsIdentifierChar(curr))
            {
                begining_index = current_index;
                begining_pos = current_pos;
                is_numeric = false;
                continue;
            }
            if (IsWhite(first) && IsOperatorChar(curr))
            {
                begining_index = current_index;
                begining_pos = current_pos;
                is_numeric = false;
                continue;
            }

            //////////////////////////////////////////////////////////////////////

            if (IsIdentifierChar(first) && IsOperatorChar(curr))
            {
                int len = current_index - begining_index;
                tokens_str->emplace_back(code.substr(begining_index, len), begining_pos);
                begining_index = current_index;
                begining_pos = current_pos;
                is_numeric = false;
                continue;
            }

            if (IsOperatorChar(first) && IsIdentifierChar(curr))
            {
                int len = current_index - begining_index;

                std::string operators_str = code.substr(begining_index, len);
                std::vector<std::string> operator_list;

                SplitConsecutiveOperators(operators_str, &operator_list);

                Position operator_pos = current_pos;

                for (int j = 0; j < operator_list.size(); j++)
                {
                    operator_pos.col += operator_list[j].size();
                    tokens_str->emplace_back(operator_list[j], operator_pos);
                }

                begining_index = current_index;
                begining_pos = current_pos;
                is_numeric = false;
                continue;
            }

            //////////////////////////////////////////////////////////////////////

            if (IsIdentifierChar(first) && IsWhite(curr))
            {
                int len = current_index - begining_index;
                tokens_str->emplace_back(code.substr(begining_index, len), begining_pos);
                begining_index = current_index;
                begining_pos = current_pos;
                is_numeric = false;
                continue;
            }

            if (IsOperatorChar(first) && IsWhite(curr))
            {
                int len = current_index - begining_index;

                std::string operators_str = code.substr(begining_index, len);
                std::vector<std::string> operator_list;

                SplitConsecutiveOperators(operators_str, &operator_list);

                Position operator_pos = begining_pos;

                for (int j = 0; j < operator_list.size(); j++)
                {
                    operator_pos.col += operator_list[j].size();
                    tokens_str->emplace_back(operator_list[j], operator_pos);
                }

                begining_index = current_index;
                begining_pos = current_pos;
                is_numeric = false;
                continue;
            }

            //////////////////////////////////////////////////////////////////////
            Error::PushError(err, Error::UnexpectedSymbolError(current_pos, curr));
            return;
        }

        return;
    }

    static void SplitConsecutiveOperators(const std::string &code, std::vector<std::string> *oper_list)
    {
        constexpr char operator_set[][3] = {":=", "**", ">=", "<=", "<>", "(", ")", "^", "-", "+", "*", "/", ">", "<", "=", "&", ":", ";", ",", "."};

        bool succesful_match;

        for (int code_pos = 0; code_pos < code.size(); /* do not increment automaticaly*/)
        {
            succesful_match = false;

            for (int oper_nr = 0; oper_nr < sizeof(operator_set) / sizeof(operator_set[0]); oper_nr++)
            {

                const char *const _operator = operator_set[oper_nr];
                int operator_len = strlen(_operator);

                std::string code_substr = code.substr(code_pos, operator_len);

                if (code_substr == _operator)
                {
                    oper_list->push_back(_operator);
                    code_pos += operator_len;
                    succesful_match = true;
                    break;
                }
            }

            if (!succesful_match)
            {
                // something went wrong - return
                // TODO - fix this
                throw "XD";
            }
        }
    }

    // [a-z, A-Z, 0-9, _]
    static bool IsIdentifierChar(char c)
    {
        return (c >= 'a' && c <= 'z') ||
               (c >= 'A' && c <= 'Z') ||
               (c >= '0' && c <= '9') ||
               (c == '_') || (c == '#');
    }

    static bool IsNumericChar(char c)
    {
        return (c >= '0' && c <= '9') ||
               (c == '#');
    }

    static bool IsWhite(char c)
    {
        return (c == '\n') ||
               (c == '\r') ||
               (c == '\t') ||
               (c == ' ');
    }

    static bool IsOperatorChar(char c)
    {
        return (c == ':') ||
               (c == '=') ||
               (c == '*') ||
               (c == '>') ||
               (c == '<') ||
               (c == '(') ||
               (c == ')') ||
               (c == '^') ||
               (c == '-') ||
               (c == '+') ||
               (c == '/') ||
               (c == '&') ||
               (c == ';') ||
               (c == '.') ||
               (c == ',');
        ;
    }

};