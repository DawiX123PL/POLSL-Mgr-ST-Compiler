#pragma once

#include <string>

bool ReadFileContent(std::string file_name, std::string *result);
bool WriteFileContent(std::string file_name, const std::string &file_content);
void PrintFileContent(std::string file_content);

