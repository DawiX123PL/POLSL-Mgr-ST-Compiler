#include "st_lexer.hpp"
#include "../error.hpp"

#include <assert.h>
#include <string>
#include <vector>
#include <array>
#include <cctype>
#include <cstring>
#include <iostream>
#include <map>
#include <regex>
#include <chrono>

namespace Lexer
{

    struct StringAndPos
    {
        std::string str;
        Position pos;
        StringAndPos(std::string _str, Position _pos) : str(_str), pos(_pos) {};
    };

    // **********************************************************************************************************************************************
    // Definitions

    class RegexBuilder
    {
        std::string pattern_str;
        int capturing_group = 0;

    public:
        std::regex Build()
        {
            return std::regex(pattern_str, std::regex_constants::syntax_option_type::ECMAScript);
        }
        int Push(std::string s)
        {
            if (!pattern_str.empty())
                pattern_str += "|";
            pattern_str += "(" + s + ")";
            capturing_group++;
            return capturing_group;
        }
    };

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

    int GetRegexMatchID(std::smatch mr)
    {
        for (int i = 1; i < mr.size(); i++)
        {
            if (mr[i].matched)
                return i;
        }
        return 0;
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

    TokenList Tokenize(Error::ErrorList_t &err, const std::string &code)
    {

        std::string identifier_or_keyword = "[a-zA-Z_][a-zA-Z0-9_]*";
        std::string integer_literal = "[0-9][0-9_]*";
        std::string numeric_literal = "[0-9][0-9_]*(?:[.][0-9][0-9_]*)?(?:[eE][+-]?[0-9][0-9_]*)?";
        std::string typed_numeric_literal = identifier_or_keyword + "#[a-zA-Z0-9._]*";
        std::string based_numeric_literal = integer_literal + "#[a-zA-Z0-9_]*";
        std::string typed_based_numeric_literal = identifier_or_keyword + "#" + integer_literal + "#[a-zA-Z0-9_]*";
        std::string string_literal1 = R"REGEX(\"(?:\$\"|[^"])*\")REGEX";
        std::string string_literal2 = R"REGEX(\'(?:\$\'|[^'])*\')REGEX";

        RegexBuilder builder;
        std::map<int, TokenType> id_map;

        const int id_newline = builder.Push("\\n");
        const int id_white_space = builder.Push("\\s");
        const int id_typed_based_numeric_literal = builder.Push(typed_based_numeric_literal);
        const int id_typed_numeric_literal = builder.Push(typed_numeric_literal);
        const int id_based_numeric_literal = builder.Push(based_numeric_literal);
        const int id_identifier_or_keyword = builder.Push(identifier_or_keyword);
        const int id_numeric_literal = builder.Push(numeric_literal);
        const int id_string_literal_1 = builder.Push(string_literal1);
        const int id_string_literal_2 = builder.Push(string_literal2);
        const int id_single_line_comment = builder.Push("\\/\\/.*");
        const int id_multiline_comment_1 = builder.Push(R"REGEX(\(\*[^*]*(?:\*(?!\*)[^)]*)*\*\))REGEX"); // todo fix problem with missing comments tags
        const int id_multiline_comment_2 = builder.Push(R"REGEX(\\\*[^*]*(?:\*(?!\*)[^*]*)*\*\\)REGEX"); // todo fix problem with missing comments tags
        id_map[builder.Push("\\(\\*")] = TokenType::COMMENT_MULTILINE_BRACKET_OPEN;
        id_map[builder.Push("\\*\\)")] = TokenType::COMMENT_MULTILINE_BRACKET_CLOSE;
        id_map[builder.Push("\\\\\\*")] = TokenType::COMMENT_MULTILINE_SLASH_OPEN;
        id_map[builder.Push("\\*\\\\")] = TokenType::COMMENT_MULTILINE_SLASH_CLOSE;
        id_map[builder.Push("\\(")] = TokenType::ROUND_BRACKET_OPENING;
        id_map[builder.Push("\\)")] = TokenType::ROUND_BRACKET_CLOSING;
        id_map[builder.Push("\\[")] = TokenType::SQUARE_BRACKET_OPENING;
        id_map[builder.Push("\\]")] = TokenType::SQUARE_BRACKET_CLOSING;
        id_map[builder.Push("\\*\\*")] = TokenType::EXPONENTIATION;
        id_map[builder.Push("\\<\\=")] = TokenType::LESS_OR_EQUAL;
        id_map[builder.Push("\\>\\=")] = TokenType::GREATER_OR_EQUAL;
        id_map[builder.Push("\\<\\>")] = TokenType::INEQUALITY;
        id_map[builder.Push("\\:\\=")] = TokenType::ASSIGN;
        id_map[builder.Push("\\.\\.")] = TokenType::DOUBLE_DOT;
        id_map[builder.Push("\\=")] = TokenType::EQUALITY;
        id_map[builder.Push("\\^")] = TokenType::DEREFERENCE;
        id_map[builder.Push("\\-")] = TokenType::MINUS;
        id_map[builder.Push("\\+")] = TokenType::PLUS;
        id_map[builder.Push("\\*")] = TokenType::MULTIPLY;
        id_map[builder.Push("\\/")] = TokenType::DIVIDE;
        id_map[builder.Push("\\>")] = TokenType::GREATER_THAN;
        id_map[builder.Push("\\<")] = TokenType::LESS_THAN;
        id_map[builder.Push("\\&")] = TokenType::BOOLEAN_AND;
        id_map[builder.Push("\\:")] = TokenType::COLON;
        id_map[builder.Push("\\;")] = TokenType::SEMICOLON;
        id_map[builder.Push("\\.")] = TokenType::DOT;
        id_map[builder.Push("\\,")] = TokenType::COMMA;
        id_map[builder.Push("\\#")] = TokenType::NUMBER_SIGN;

        std::regex pattern = builder.Build();
        std::smatch mr;

        // ***************************
        TokenList tokens;

        int line_counter = 1;
        int current_column_begin = 0;

        auto start_time = std::chrono::high_resolution_clock::now();

        auto next_str = code.begin();
        auto end_str = code.end();
        while (std::regex_search(next_str, end_str, mr, pattern))
        {
            int current_index = next_str - code.begin();
            next_str = mr.suffix().first;

            Position pos{line_counter, current_index - current_column_begin};
            if (mr.empty())
            {
                Error::PushError(err, Error::UnexpectedSymbolError(pos, code[current_index]));
                continue;
            }

            int id = GetRegexMatchID(mr);

            if (id == id_newline)
            {
                line_counter++;
                current_column_begin = code.begin() - next_str;
                continue;
            }

            if (id == id_white_space ||
                id == id_single_line_comment ||
                id == id_multiline_comment_1 ||
                id == id_multiline_comment_2)
            {
                continue;
            }

            if (id == id_numeric_literal ||
                id == id_typed_numeric_literal ||
                id == id_based_numeric_literal ||
                id == id_typed_based_numeric_literal)
            {
                TokenType type = TokenType::NUMERIC_LITERAL;
                tokens.emplace_back(type, mr.str(), pos);
                continue;
            }

            if (id == id_identifier_or_keyword)
            {
                Token token;
                if (TryCategoriseKeywordToken(mr[0].str(), &token))
                {
                    tokens.emplace_back(token.type, mr.str(), pos);
                }
                else
                {
                    tokens.emplace_back(TokenType::IDENTIFIER, mr.str(), pos);
                }
                continue;
            }

            auto iter = id_map.find(id);
            if (iter != id_map.end())
            {
                TokenType type = iter->second;
                tokens.emplace_back(type, mr.str(), pos);
                continue;
            }
            else
            {
                Error::PushError(err, Error::UnexpectedSymbolError(pos, code[current_index]));
                continue;
            }
        }

        auto stop_time = std::chrono::high_resolution_clock::now();
        float time_ms = ((float)(stop_time - start_time).count()) / 1000000.0;
        std::cout << "time: " << time_ms << "ms\n";
        std::cout.flush();

        return tokens;
    }

};
