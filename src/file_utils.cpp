#include "file_utils.hpp"
#include "console_color.hpp"
#include <fstream>
#include <memory>
#include <iostream>

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

void PrintFileContent(std::string file_content)
{
    constexpr int iter_hardlimit = 10000;

    int current_pos = 0;
    for(int i = 0; i < iter_hardlimit; i++)
    {
        int newline_pos = file_content.find("\n", current_pos);
        if (newline_pos < 0)
            break;

        std::cout << Console::FgBrightGreen("[File]: ") << file_content.substr(current_pos, newline_pos - current_pos + 1);

        current_pos = newline_pos + 1;
    }
}
