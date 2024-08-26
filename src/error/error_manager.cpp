
#include "error_manager.hpp"
#include "console/color.hpp"

ErrorManager::ErrorList_t ErrorManager::error_list = {};

std::ostream &operator<<(std::ostream &os, Error::BasicError const &error)
{
    return os << error.ToString();
}

