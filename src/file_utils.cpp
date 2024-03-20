#include "file_utils.hpp"
#include <fstream>

bool ReadFileContent(std::string file_name, std::string *result)
{
    try
    {
        std::fstream file(file_name, std::ios::in | std::ios::binary);

        if (!file.good())
        {
            return false;
        }

        file.seekg(0, file.end);
        int file_length = file.tellg();
        file.seekg(0, file.beg);

        auto buffer = std::make_unique<char[]>(file_length);

        file.read(buffer.get(), file_length);
        result->assign(buffer.get(), file_length);

        file.close();

        return true;
    }
    catch (...)
    {
        return false;
    }

    return true;
}