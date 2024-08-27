#pragma once

#include <inttypes.h>
#include <string>
#include <filesystem>
#include <memory>
#include "console/color.hpp"

struct Position
{
    int line;
    int col;
    std::shared_ptr<std::filesystem::path> src;

    Position(std::shared_ptr<std::filesystem::path> _src, int _line, int _col) : src(_src), line(_line), col(_col){};

    std::string ToStringShort() const
    {
        std::string source = src ? src->filename().string() : "";
        return "{" + source + ", ln:" + std::to_string(line) + ", col:" + std::to_string(col) + "}";
    }
    
    std::string ToString() const
    {
        std::string source = src ? src->string() : "";
        std::string pos_str = "{" + source + ", Line " + std::to_string(line) + ", Column " + std::to_string(col) + "}";
        return Console::FgBrightRed(pos_str);
    }
    
    // std::string ToString() const
    // {
    //     std::string source = src ? src->string() : "";
    //     return  source + "(" + std::to_string(line) + "," + std::to_string(col) + "):";
    // }
};
