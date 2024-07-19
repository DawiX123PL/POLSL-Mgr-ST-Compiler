#include "error.hpp"
#include "console/color.hpp"

namespace Error
{

    std::ostream &operator<<(std::ostream &os, BasicError const &error)
    {
        return os << error.ToString();
    }

    void PrintErrors(const ErrorList_t &error_list)
    {
        for (int i = 0; i < error_list.size(); i++)
        {
            std::cout << Console::FgBrightRed("[Error]") << *error_list[i] << "\n";
        }
    }

}