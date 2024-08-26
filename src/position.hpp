#pragma once

#include <inttypes.h>
#include <string>

struct Position
{
    int line;
    int col;

    Position(int _line, int _col) : line(_line), col(_col){};

    std::string ToStringShort() const
    {
        return "{ln:" + std::to_string(line) + ", col:" + std::to_string(col) + "}";
    }
    std::string ToString() const
    {
        return "{Line " + std::to_string(line) + ", Column " + std::to_string(col) + "}";
    }
};
