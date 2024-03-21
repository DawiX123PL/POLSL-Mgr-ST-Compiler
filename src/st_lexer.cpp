#include "st_lexer.hpp"
#include "error.hpp"

#include <string>
#include <vector>
#include <array>
#include <cctype>
#include <cstring>
#include <iostream>

struct StringAndPos
{
    std::string str;
    Pos pos;
    StringAndPos(std::string _str, Pos _pos) : str(_str), pos(_pos){};
};

// **********************************************************************************************************************************************
// Declarations
bool IsSubstrAtPos(const std::string &code, int pos, char *sub_str);
std::vector<Error> SplitToSubstrings(const std::string &code, std::vector<StringAndPos> *tokens_str);
void SplitConsecutiveOperators(const std::string &code, std::vector<std::string> *oper_list);

bool IsIdentifierChar(char c);
bool IsWhite(char c);
bool IsOperatorChar(char c);

// **********************************************************************************************************************************************
// Definitions

std::vector<Error> Tokenize(const std::string &code, std::vector<Token> *tokens)
{

    std::vector<Error> err_list;
    std::vector<StringAndPos> tokens_str;

    err_list = SplitToSubstrings(code, &tokens_str);

    std::cout << Console::FgBrightBlue("[TOKEN COUNT]: ") << tokens_str.size() << "\n";
    for (int i = 0; i < tokens_str.size(); i++)
    {
        std::cout << Console::FgBrightBlue("[TOKEN]: ") << tokens_str[i].str << "\n";
    }

    return {}; // OK
}

std::vector<Error> CategoriseTokens(const std::vector<StringAndPos> &tokens_str, std::vector<Token> *tokens)
{
    tokens->clear();
    tokens->reserve(tokens_str.size());

    for (int token_index; token_index < tokens_str.size(); token_index++)
    {
        std::string str = tokens_str[token_index].str;
        Pos pos = tokens_str[token_index].pos;

        for (int keyword_index; keyword_index < keywords_list_size; keyword_index++)
        {
            char * keyword = keywords_list[keyword_index].first;
            Token::TokenType token = keywords_list[keyword_index].second;

            if(str == keyword){
                tokens->emplace_back(token);
                break;
            }
        }
    }

    return {};
}

std::vector<Error> SplitToSubstrings(const std::string &code, std::vector<StringAndPos> *tokens_str)
{

    char prev = ' ';
    char curr = ' ';

    int begining_index = 0;
    Pos pos(0, 0);

    //                                  !!!!!!      this is NOT mistake       !!!!!!
    //                      this is used to force one additional loop pass to put remaining data to tokens_str
    //                                                       |
    //                                                       V
    //                                                  ... + 1; ...
    for (int current_index = 0; current_index < code.size() + 1; current_index++)
    {

        prev = curr;
        if (current_index < code.size())
        {
            curr = code[current_index];
        }
        else
        {
            curr = ' '; //  artifialy add white char at the end
        }

        if (IsIdentifierChar(prev) && IsIdentifierChar(curr))
        {
            // do nothing - skip
            continue;
        }
        if (IsWhite(prev) && IsWhite(curr))
        {
            // do nothing - skip
            continue;
        }

        if (IsOperatorChar(prev) && IsOperatorChar(curr))
        {
            // do nothing - skip
            continue;
        }

        //////////////////////////////////////////////////////////////////////

        if (IsWhite(prev) && IsIdentifierChar(curr))
        {
            begining_index = current_index;
            continue;
        }
        if (IsWhite(prev) && IsOperatorChar(curr))
        {
            begining_index = current_index;
            continue;
        }

        //////////////////////////////////////////////////////////////////////

        if (IsIdentifierChar(prev) && IsOperatorChar(curr))
        {
            int len = current_index - begining_index;
            tokens_str->emplace_back(code.substr(begining_index, len), pos);
            begining_index = current_index;
            continue;
        }

        if (IsOperatorChar(prev) && IsIdentifierChar(curr))
        {
            int len = current_index - begining_index;

            std::string operators_str = code.substr(begining_index, len);
            std::vector<std::string> operator_list;

            SplitConsecutiveOperators(operators_str, &operator_list);

            Pos operator_pos = pos;

            for (int j = 0; j < operator_list.size(); j++)
            {
                operator_pos.col += operator_list[j].size();
                tokens_str->emplace_back(operator_list[j], operator_pos);
            }

            begining_index = current_index;
            continue;
        }

        //////////////////////////////////////////////////////////////////////

        if (IsIdentifierChar(prev) && IsWhite(curr))
        {
            int len = current_index - begining_index;
            tokens_str->emplace_back(code.substr(begining_index, len), pos);
            begining_index = current_index;
            continue;
        }

        if (IsOperatorChar(prev) && IsWhite(curr))
        {
            int len = current_index - begining_index;

            std::string operators_str = code.substr(begining_index, len);
            std::vector<std::string> operator_list;

            SplitConsecutiveOperators(operators_str, &operator_list);

            Pos operator_pos = pos;

            for (int j = 0; j < operator_list.size(); j++)
            {
                operator_pos.col += operator_list[j].size();
                tokens_str->emplace_back(operator_list[j], operator_pos);
            }
            begining_index = current_index;
            continue;
        }

        //////////////////////////////////////////////////////////////////////

        return {Error(Error::ErrorType::UNEXPECTED_SYMBOL, "Unexpected symbol (ASCI \'" + std::string(1, curr) + "\' ;code:" + std::to_string((int)curr) + ") at position .... ")};
    }

    return {};
}

void SplitConsecutiveOperators(const std::string &code, std::vector<std::string> *oper_list)
{
    constexpr char operator_set[][3] = {":=", "**", ">=", "<=", "<>", "(", ")", "^", "-", "+", "*", "/", ">", "<", "=", "&", ":", ";", "#"};

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
bool IsIdentifierChar(char c)
{
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9') ||
           (c == '_');
}

bool IsWhite(char c)
{
    return (c == '\n') ||
           (c == '\r') ||
           (c == '\t') ||
           (c == ' ');
}

bool IsOperatorChar(char c)
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
           (c == '#');
}
