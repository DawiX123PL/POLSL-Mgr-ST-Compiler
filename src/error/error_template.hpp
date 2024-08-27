#pragma once
#include <string>
#include "position.hpp"
#include "console/color.hpp"

namespace Error
{

    class BasicError
    {
    public:
        virtual std::string MessageToString() const = 0;

    public:
        std::string ToString() const
        {
            return Console::FgDarkRed("[Error]") + MessageToString();
        }
    };

    class BasicPosinionalError : public BasicError
    {
        Position pos;
    public:
        BasicPosinionalError(Position _pos): pos(_pos){}

    public:
        std::string ToString() const
        {
            return Console::FgDarkRed("[Error]") + pos.ToString() + " " + MessageToString();
        }
    };

};