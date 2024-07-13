#pragma once

#include <string>
#include <vector>
#include "../error.hpp"

struct File
{
    std::string path;
    std::string content;
};


// returns true if operation was successful
bool ReadFile(Error::ErrorList_t err, std::string path, File* file);

// returns vector of successfuly read files
std::vector<File> ReadFileList(Error::ErrorList_t err, std::vector<std::string> path_list);


