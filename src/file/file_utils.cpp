#include "file_utils.hpp"
#include "../console/color.hpp"
#include <fstream>
#include <memory>
#include <iostream>

static bool ReadFileContent(std::string file_name, std::string *result);
static bool WriteFileContent(std::string file_name, const std::string &file_content);
static void PrintFileContent(std::string file_content);


// returns true if operation was successful
bool ReadFile(Error::ErrorList_t err, std::string path, File* file)
{
    file->path = path;
    file->content = "";
    
    if(!ReadFileContent(path, &file->content))
    {
        Error::PushError(err, Error::CannotReadFile(path));
        return false;
    }

    return true;
}

std::vector<File> ReadFileList(Error::ErrorList_t err, std::vector<std::string> path_list)
{
    std::vector<File> files; 

    for(int i = 0; i < path_list.size(); i++)
    {
        File f;
        if(ReadFile(err, path_list[i], &f))
        {
            files.push_back(f);
        }
    }

    return files; 
}

// returns true if operation was successful
static bool ReadFileContent(std::string file_name, std::string *result)
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

static bool WriteFileContent(std::string file_name, const std::string &file_content)
{
    try
    {
        std::fstream file(file_name, std::ios::out | std::ios::binary);

        if (!file.good())
        {
            return false;
        }

        file.write(file_content.c_str(), file_content.size());
        file.close();

        return true;
    }
    catch (...)
    {
        return false;
    }

    return true;
}

static void PrintFileContent(std::string file_content)
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
