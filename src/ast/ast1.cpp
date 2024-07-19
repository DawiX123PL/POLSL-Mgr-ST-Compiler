
#include "ast1.hpp"

namespace AST
{

    std::string Indent(std::string str)
    {
        std::string new_str = "\t";
        for (int i = 0; i < str.size(); i++)
        {
            char c = str[i];
            new_str.push_back(c);
            if (c == '\n')
            {
                new_str.push_back('\t');
            }
        }
        return new_str;
    }

    std::string StatementListToString(StmtList list)
    {
        std::string str = "";
        bool first = true;

        for (StmtPtr stmt : list)
        {
            std::string stmt_str = stmt ? stmt->ToString() : "____";

            if (!first)
            {
                str += "\n" + stmt_str;
            }
            else
            {
                str += stmt_str;
                first = false;
            }
        }
        return Indent(str);
    }
}



