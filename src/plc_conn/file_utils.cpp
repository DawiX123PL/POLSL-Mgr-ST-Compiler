#include "file_utils.hpp"

#include <fstream>

bool ReadFile(std::string file_name, std::vector<uint8_t> *content)
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

        content->resize(file_length);
        auto begin = &*content->begin();
        file.read((char *)begin, content->size());

        file.close();

        return true;
    }
    catch (...)
    {
        return false;
    }

    return true;
}