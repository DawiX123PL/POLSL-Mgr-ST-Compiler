#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

enum class ArgFlag
{
    Help,     // -h, --help
    Verbose,  // -v, --verbose
    FilePath, // -f, --file
};

const char *ArgFlagToStr(ArgFlag flag);

std::vector<std::string> ArgsToStrList(int argc, char **argv);
std::map<ArgFlag, std::string> ArgsToMap(int argc, char **argv);

void PrintArgs(const std::map<ArgFlag, std::string> &args);
bool IsArgsContain(const std::map<ArgFlag, std::string> &args, ArgFlag flag);
