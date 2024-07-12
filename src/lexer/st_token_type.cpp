#include <utility>
#include "st_token_type.hpp"

namespace Lexer
{

    const char *TokenTypeToString(TokenType type)
    {
        constexpr int count = sizeof(tokentype_names_list) / sizeof(tokentype_names_list[0]);
        for (int i = 0; i < count; i++)
        {
            TokenType t = tokentype_names_list[i].second;

            if (t == type)
            {
                return tokentype_names_list[i].first;
            }
        }

        return "UNNOWN";
    }

}