#pragma once

#include <utility>
#include <assert.h>
#include "error/error_manager.hpp"
#include "frontend/lexer/st_lexer.hpp"
#include "frontend/ast/ast1.hpp"
#include <regex>

namespace StParser::Expression
{

    class RecursiveDescendParser
    {
        Lexer::TokenList tokens;
        int current_index = 0;

        void PopToken()
        {
            current_index++;
        }

        bool IsNextToken(Lexer::TokenType type)
        {
            if (current_index < tokens.size())
            {
                return tokens[current_index].type == type;
            }
            return false;
        }

        // because of this function Recursive Descend Parser is now LL(2)
        bool IsNextToken(Lexer::TokenType t1, Lexer::TokenType t2)
        {
            if (current_index + 1 < tokens.size())
            {
                return tokens[current_index].type == t1 && tokens[current_index + 1].type == t2;
            }
            return false;
        }

        [[nodiscard]] Lexer::Token GetCurrentToken()
        {
            // todo
            if (current_index < tokens.size())
            {
                return tokens[current_index];
            }
            else
            {
                return Lexer::Token(Lexer::TokenType::UNNOWN, "", Position(nullptr, 0, 0)); // to prevent segfault
            }
        }

    public:

        //  void Parse Expression()
        // {
        //     Parse Expression();

        //     while (IsNextToken(Lexer::TokenType::BOOLEAN_XOR))
        //     {
        //         PopToken();
        //         Parse Expression();
        //     }
        // }

        // AST::ExprPtr ParseNumericLiteral()
        // {

        //     Lexer::Token token = tokens[current_index];

        //     //
        // }

        [[nodiscard]] bool ParseFloat(std::string str, double *result)
        {
            std::string str1;
            // step1: skip _
            for (char c : str)
            {
                if (c != '_')
                    str1 += c;
            }

            try
            {
                *result = std::stold(str1);
                return true;
            }
            catch (...)
            {
                return false;
            }
            return false;
        }

        static int CharToNum(char c)
        {
            if (c >= '0' && c <= '9')
            {
                return (int)c - (int)'0';
            }

            if (c >= 'a' && c <= 'z')
            {
                return (int)c - (int)'a' + 0x0A;
            }

            if (c >= 'A' && c <= 'Z')
            {
                return (int)c - (int)'A' + 0x0A;
            }

            return -1;
        }

        bool ParseInteger(const std::string str, int base, big_int *result)
        {
            big_int res;
            bool minus = false;
            for (int i = 0; i < str.size(); i++)
            {
                char c = str[i];
                if (i == 0 & c == '+')
                    continue;

                if (i == 0 & c == '-')
                {
                    minus = true;
                    continue;
                }

                if (c == '_')
                    continue;

                int n = CharToNum(c);
                if (n == -1 && n >= base)
                {
                    return false;
                }
                res *= base;
                res += n;
            }

            *result = minus ? -res : res;
            return true;
        }

        /////////////////////////////////////////////////////////////////////////////////

        [[nodiscard]] AST::ExprPtr
        ParseNumericLiteral()
        {
            Lexer::Token token = GetCurrentToken();
            PopToken();

            std::smatch mr;

            // check if bool literal
            if (std::regex_match(token.str, mr, std::regex("FALSE|BOOL#0|BOOL#FALSE", std::regex_constants::syntax_option_type::icase)))
            {
                AST::Type type = AST::Type::BOOL;
                return AST::MakeExpr(AST::Literal(false));
            }

            if (std::regex_match(token.str, mr, std::regex("TRUE|BOOL#1|BOOL#TRUE", std::regex_constants::syntax_option_type::icase)))
            {
                AST::Type type = AST::Type::BOOL;
                return AST::MakeExpr(AST::Literal(true));
            }

            // check if integer (arbitrary precision)
            if (std::regex_match(token.str, mr, std::regex("[0-9][0-9_]*")))
            {
                big_int num;
                if (!ParseInteger(token.str, 10, &num))
                {
                    ErrorManager::Create(Error::InvalidNumericLiteral(token.pos));
                }
                AST::Type type = AST::Type::INT;
                return AST::MakeExpr(AST::Literal(num, type));
            }

            // check if float
            if (std::regex_match(token.str, mr, std::regex("[0-9][0-9_]*[.][0-9][0-9_]?(?:[eE][+-]?[0-9][0-9_]*)?")))
            {
                double num;
                AST::Type type = AST::Type::REAL;
                if (!ParseFloat(token.str, &num))
                {
                    ErrorManager::Create(Error::InvalidNumericLiteral(token.pos));
                }
                return AST::MakeExpr(AST::Literal(num, type));
            }

            // typed numeric literal
            if (std::regex_match(token.str, mr, std::regex("(.*)#(.*)")))
            {
                // float types
                AST::Type type = AST::Type::FromString(mr[1].str());
                if (type.IsFloatingPoint())
                {
                    double num;
                    if (!ParseFloat(mr[2].str(), &num))
                    {
                        ErrorManager::Create(Error::InvalidNumericLiteral(token.pos));
                    }
                    return AST::MakeExpr(AST::Literal(num, type));
                }

                // integer like types
                if (type.IsInteger() || type.IsBit())
                {
                    big_int num;
                    if (!ParseInteger(mr[2].str(), 10, &num))
                    {
                        ErrorManager::Create(Error::InvalidNumericLiteral(token.pos));
                    }
                    return AST::MakeExpr(AST::Literal(num, type));
                }
            }

            // TODO:
            // typed and based numeric literal

            ErrorManager::Create(Error::InvalidNumericLiteral(token.pos));
            return nullptr;
        }

        [[nodiscard]] AST::ExprPtr GlobalMemoryAccess()
        {
            Lexer::Token token = GetCurrentToken();
            PopToken();

            std::smatch mr;
            if (!std::regex_match(token.str, mr, std::regex("%([IQM])([XBWDL]?)([0-9]+(?:.[0-9]+)*)")))
            {
                ErrorManager::Create(Error::InvalidGlobalAddress(token.pos));
                return nullptr;
            }

            AST::GlobalMemoryAccess mem_access;

            std::map<std::string, AST::GlobalMemoryAccess::Location> location_names = {
                {"I", AST::GlobalMemoryAccess::Location::Input},
                {"Q", AST::GlobalMemoryAccess::Location::Output},
                {"M", AST::GlobalMemoryAccess::Location::Memory}};

            auto loc = location_names.find(mr[1].str());
            if (loc == location_names.end())
            {
                ErrorManager::Create(Error::InvalidGlobalAddress(token.pos));
                return nullptr;
            }

            mem_access.location = loc->second;

            std::map<std::string, uint64_t> size_names = {
                {"", 1},
                {"X", 1},
                {"B", 8},
                {"W", 16},
                {"D", 32},
                {"L", 64},
            };

            auto size = size_names.find(mr[2].str());
            if (size == size_names.end())
            {
                ErrorManager::Create(Error::InvalidGlobalAddress(token.pos));
                return nullptr;
            }

            mem_access.size = size->second;

            std::string::const_iterator next_str = token.str.begin();
            std::string::const_iterator end_str = token.str.end();
            while (std::regex_search(next_str, end_str, mr, std::regex("[0-9]+")))
            {
                next_str = mr.suffix().first;

                big_int address_num;
                ParseInteger(mr[0].str(), 10, &address_num);

                mem_access.address.emplace_back(address_num);
            }

            return AST::MakeExpr(mem_access);
        }

        // function calls
        // ```st
        // /*non-formal:*/             LIMIT(B, 0, 5)
        // /*formal (no arguments):*/  LIMIT()
        // /*formal:*/                 LIMIT(IN := B, MN := 0, MX := 0)
        //                             LIMIT(IN => B, MN => 0, MX := 0)
        // ```
        void ParseArgumentList(
            std::vector<AST::ExprPtr> *non_formal_args,
            std::vector<std::pair<AST::ExprPtr, AST::ExprPtr>> *formal_input_args,
            std::vector<std::pair<AST::ExprPtr, AST::ExprPtr>> *formal_output_args)
        {
            bool is_formal = false;
            bool is_non_formal = false;

            while (true)
            {
                AST::ExprPtr expr = ParseExpression();
                non_formal_args->push_back(expr);

                if (!is_formal && IsNextToken(Lexer::TokenType::COLON))
                {
                    PopToken();
                    is_non_formal = true;
                    continue;
                }

                if (!is_non_formal && IsNextToken(Lexer::TokenType::ASSIGN))
                {
                    PopToken();
                    is_formal = true;

                    AST::ExprPtr right_expr = ParseExpression();
                    formal_input_args->emplace_back(expr, right_expr);
                }
                else if (!is_non_formal && IsNextToken(Lexer::TokenType::RIGHT_ASSIGN))
                {
                    PopToken();
                    is_formal = true;

                    AST::ExprPtr right_expr = ParseExpression();
                    formal_output_args->emplace_back(expr, right_expr);
                }

                if (IsNextToken(Lexer::TokenType::COLON))
                {
                    PopToken();
                    continue;
                }

                break;
            }

            if (is_formal)
            {
                non_formal_args->clear();
            }
            if (is_non_formal)
            {
                formal_input_args->clear();
                formal_output_args->clear();
            }
        }

        [[nodiscadr]] AST::ExprPtr ParseFunctionCall()
        {
            if (!IsNextToken(Lexer::TokenType::IDENTIFIER))
            {
                ErrorManager::Create(Error::ExpectedKeyword(GetCurrentToken().pos, Lexer::TokenType::IDENTIFIER));
                return nullptr;
            }

            std::string callee_name = GetCurrentToken().str; // name
            PopToken();

            if (!IsNextToken(Lexer::TokenType::ROUND_BRACKET_OPENING))
            {
                ErrorManager::Create(Error::ExpectedKeyword(GetCurrentToken().pos, Lexer::TokenType::ROUND_BRACKET_OPENING));
                return nullptr;
            }

            PopToken();

            if (IsNextToken(Lexer::TokenType::ROUND_BRACKET_CLOSING))
            {
                PopToken();
                return AST::MakeExpr(AST::FormalCall(callee_name));
            }

            std::vector<AST::ExprPtr> non_formal_args;
            std::vector<std::pair<AST::ExprPtr, AST::ExprPtr>> formal_input_args;
            std::vector<std::pair<AST::ExprPtr, AST::ExprPtr>> formal_output_args;

            ParseArgumentList(&non_formal_args,
                              &formal_input_args,
                              &formal_output_args);

            if (!IsNextToken(Lexer::TokenType::ROUND_BRACKET_CLOSING))
            {
                ErrorManager::Create(Error::ExpectedKeyword(GetCurrentToken().pos, Lexer::TokenType::ROUND_BRACKET_CLOSING));
                return nullptr;
            }

            PopToken();

            if (non_formal_args.size())
            {
                return AST::MakeExpr(AST::NonformalCall(callee_name, non_formal_args));
            }

            if (formal_input_args.size() || formal_output_args.size())
            {
                return AST::MakeExpr(AST::FormalCall(callee_name, formal_input_args, formal_output_args));
            }

            return AST::MakeExpr(AST::FormalCall(callee_name));
        }

        [[nodiscard]] AST::ExprPtr ParsePrimaryExpression()
        {
            // TODO:
            // - [ ] check for constant (literal of every type)
            //     - [x] numeric literal
            //     - [ ] char literal
            //     - [ ] time literal
            //     - [ ] bit string literal
            //     - [x] bool literal
            // - [ ] check for enum_value
            // - [ ] check for variable access
            // - [ ] check for function call
            // - [x] check for parenteses

            if (IsNextToken(Lexer::TokenType::NUMERIC_LITERAL) ||
                IsNextToken(Lexer::TokenType::TRUE) ||
                IsNextToken(Lexer::TokenType::FALSE))
            {
                AST::ExprPtr expr = ParseNumericLiteral();
                return expr;
            }

            else if (IsNextToken(Lexer::TokenType::IDENTIFIER, Lexer::TokenType::ROUND_BRACKET_OPENING))
            {
                AST::ExprPtr expr = ParseFunctionCall();
                return expr;
            }

            else if (IsNextToken(Lexer::TokenType::IDENTIFIER))
            {
                // TODO: parse
                Lexer::Token token = GetCurrentToken();
                PopToken();

                AST::ExprPtr expr = AST::MakeExpr(AST::VariableAccess(token.str));
                return expr;
            }

            else if (IsNextToken(Lexer::TokenType::MEMORY_ADDRESS))
            {
                AST::ExprPtr expr = GlobalMemoryAccess();
                return expr;
            }

            else if (IsNextToken(Lexer::TokenType::ROUND_BRACKET_OPENING))
            {
                PopToken();

                AST::ExprPtr expr = ParseExpression();

                if (IsNextToken(Lexer::TokenType::ROUND_BRACKET_CLOSING))
                {
                    PopToken();
                }
                else
                {
                    // Error Expected closing bracket ')'
                    ErrorManager::Create(Error::ExpectedKeyword(GetCurrentToken().pos, Lexer::TokenType::ROUND_BRACKET_CLOSING));
                }
                return expr;
            }

            // Error: Expected Literal or opening Bracket '('
            ErrorManager::Create(Error::ExpectedKeyword(GetCurrentToken().pos, Lexer::TokenType::NUMERIC_LITERAL));
            return nullptr;
        }

        [[nodiscard]] AST::ExprPtr ParseUnaryExpression()
        {
            if (IsNextToken(Lexer::TokenType::PLUS) ||
                IsNextToken(Lexer::TokenType::MINUS) ||
                IsNextToken(Lexer::TokenType::NEGATION))
            {
                Lexer::TokenType type = tokens[current_index].type;

                PopToken();
                // todo: parse
                AST::ExprPtr expr = ParsePrimaryExpression();

                if (type == Lexer::TokenType::PLUS)
                    return AST::MakeExpr(AST::UnaryPlus(expr));

                if (type == Lexer::TokenType::MINUS)
                    return AST::MakeExpr(AST::UnaryMinus(expr));

                if (type == Lexer::TokenType::NEGATION)
                    return AST::MakeExpr(AST::Negation(expr));
            }

            return ParsePrimaryExpression();
        }

        [[nodiscard]] AST::ExprPtr ParsePowerExpression()
        {
            AST::ExprPtr left = ParseUnaryExpression();

            while (IsNextToken(Lexer::TokenType::EXPONENTIATION))
            {
                PopToken();
                AST::ExprPtr right = ParseUnaryExpression();

                left = AST::MakeExpr(AST::Exponentiation(left, right));
            }

            return left;
        }

        [[nodiscard]] AST::ExprPtr ParseTerm()
        {
            AST::ExprPtr left = ParsePowerExpression();

            while (IsNextToken(Lexer::TokenType::MULTIPLY) ||
                   IsNextToken(Lexer::TokenType::DIVIDE) ||
                   IsNextToken(Lexer::TokenType::MODULO))
            {
                Lexer::TokenType type = tokens[current_index].type;

                PopToken();
                AST::ExprPtr right = ParsePowerExpression();

                if (type == Lexer::TokenType::MULTIPLY)
                    left = AST::MakeExpr(AST::Multiply(left, right));

                if (type == Lexer::TokenType::DIVIDE)
                    left = AST::MakeExpr(AST::Divide(left, right));

                if (type == Lexer::TokenType::MODULO)
                    left = AST::MakeExpr(AST::Modulo(left, right));
            }

            return left;
        }

        [[nodiscard]] AST::ExprPtr ParseAddExpression()
        {
            AST::ExprPtr left = ParseTerm();

            while (IsNextToken(Lexer::TokenType::PLUS) ||
                   IsNextToken(Lexer::TokenType::MINUS))
            {
                Lexer::TokenType type = tokens[current_index].type;

                PopToken();
                AST::ExprPtr right = ParseTerm();

                if (type == Lexer::TokenType::PLUS)
                    left = AST::MakeExpr(AST::Add(left, right));

                if (type == Lexer::TokenType::MINUS)
                    left = AST::MakeExpr(AST::Subtract(left, right));
            }

            return left;
        }

        [[nodiscard]] AST::ExprPtr ParseEqualityExpression()
        {
            AST::ExprPtr left = ParseAddExpression();

            while (IsNextToken(Lexer::TokenType::GREATER_THAN) ||
                   IsNextToken(Lexer::TokenType::LESS_THAN) ||
                   IsNextToken(Lexer::TokenType::GREATER_OR_EQUAL) ||
                   IsNextToken(Lexer::TokenType::LESS_OR_EQUAL))
            {
                Lexer::TokenType type = tokens[current_index].type;

                PopToken();
                AST::ExprPtr right = ParseAddExpression();

                if (type == Lexer::TokenType::GREATER_THAN)
                    left = AST::MakeExpr(AST::Gt(left, right));

                if (type == Lexer::TokenType::LESS_THAN)
                    left = AST::MakeExpr(AST::Lt(left, right));

                if (type == Lexer::TokenType::GREATER_OR_EQUAL)
                    left = AST::MakeExpr(AST::Geq(left, right));

                if (type == Lexer::TokenType::LESS_OR_EQUAL)
                    left = AST::MakeExpr(AST::Leq(left, right));
            }

            return left;
        }

        [[nodiscard]] AST::ExprPtr ParseCompareExpression()
        {
            AST::ExprPtr left = ParseEqualityExpression();

            while (IsNextToken(Lexer::TokenType::EQUALITY) ||
                   IsNextToken(Lexer::TokenType::INEQUALITY))
            {
                Lexer::TokenType type = tokens[current_index].type;

                PopToken();
                AST::ExprPtr right = ParseEqualityExpression();

                if (type == Lexer::TokenType::EQUALITY)
                    left = AST::MakeExpr(AST::Eq(left, right));

                if (type == Lexer::TokenType::INEQUALITY)
                    left = AST::MakeExpr(AST::Neq(left, right));
            }

            return left;
        }

        [[nodiscard]] AST::ExprPtr ParseAndExpression()
        {
            AST::ExprPtr left = ParseCompareExpression();

            while (IsNextToken(Lexer::TokenType::BOOLEAN_AND))
            {
                PopToken();
                AST::ExprPtr right = ParseCompareExpression();
                left = AST::MakeExpr(AST::And(left, right));
            }

            return left;
        }

        [[nodiscard]] AST::ExprPtr ParseXorExpression()
        {
            AST::ExprPtr left = ParseAndExpression();

            while (IsNextToken(Lexer::TokenType::BOOLEAN_XOR))
            {
                PopToken();
                AST::ExprPtr right = ParseAndExpression();
                left = AST::MakeExpr(AST::Xor(left, right));
            }

            return left;
        }

        [[nodiscard]] AST::ExprPtr ParseExpression()
        {
            AST::ExprPtr left = ParseXorExpression();

            while (IsNextToken(Lexer::TokenType::BOOLEAN_OR))
            {
                PopToken();
                AST::ExprPtr right = ParseXorExpression();
                left = AST::MakeExpr(AST::Or(left, right));
            }

            return left;
        }

        [[nodiscard]] AST::ExprPtr Parse(Lexer::TokenList _tokens)
        {
            tokens = _tokens;
            current_index = 0;
            AST::ExprPtr expr = ParseExpression();

            // check if all tokens were consumed
            if (current_index < tokens.size())
            {
                ErrorManager::Create(Error::UnexpectedTokenError(GetCurrentToken().pos, GetCurrentToken().type));
            }

            return expr;
        }
    };

    AST::ExprPtr Parse(Lexer::TokenList tokens);
}