#include "error.hpp"

namespace Error
{

    std::ostream &operator<<(std::ostream &os, BasicError const &error)
    {
        return os << error.ToString();
    }

}