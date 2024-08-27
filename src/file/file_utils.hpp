#pragma once

#include <string>
#include <vector>
#include "error/error_manager.hpp"
#include <filesystem>

struct File
{
    std::filesystem::path path;
    std::string content;
};


// returns true if operation was successful
bool ReadFile(std::string path, File* file);

// returns vector of successfuly read files
std::vector<File> ReadFileList(std::vector<std::string> path_list);

// returns true if operation was successful
bool WriteFile(File* file);
