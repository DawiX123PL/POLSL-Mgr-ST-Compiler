#pragma once

#include <string>
#include "console/color.hpp"

class Error
{

public:
    enum class ErrorType
    {
        OK,
        UNNOWN,
        UNEXPECTED_SYMBOL,
    };

    ErrorType type;
    std::string msg;

    Error() : type(ErrorType::OK), msg(){};
    Error(std::string _msg) : type(ErrorType::UNNOWN), msg(_msg){};
    Error(ErrorType _type, std::string _msg) : type(_type), msg(_msg){};
    Error(ErrorType _type) : type(_type), msg(){};

    operator bool()
    {
        return type != ErrorType::OK;
    }

    std::string ToString()
    {
        if (msg.size())
        {
            return ErrorTypeToString(type) + ": " + msg + "\n";
        }
        else
        {
            return ErrorTypeToString(type) + "\n";
        }
    }

    std::string ErrorTypeToString(ErrorType _type)
    {
        switch (_type)
        {
        case ErrorType::OK:
            return "OK";
        case ErrorType::UNNOWN:
            return "UNNOWN";
        case ErrorType::UNEXPECTED_SYMBOL:
            return "UNEXPECTED_SYMBOL";
        default:
            return "UNNOWN";
        }
    }
};
