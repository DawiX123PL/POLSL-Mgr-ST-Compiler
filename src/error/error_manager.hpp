#pragma once

#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "console/color.hpp"
#include "frontend/lexer/st_token_type.hpp"

#include "error/error_template.hpp"
#include "error/error.hpp"

class ErrorManager
{
public:
    ErrorManager() = delete;
    ~ErrorManager() = delete;

    //*****************************************************************************************************
    // Error List
private:

    typedef std::vector<std::shared_ptr<Error::BasicError>> ErrorList_t;
    static ErrorList_t error_list;

public:
    //*****************************************************************************************************
    // helper function for creating an printing errors

    // create error and print immediately
    template <typename T>
    static void Create(const T error)
    {
        error_list.push_back(std::make_shared<T>(error));
        std::cout << error.ToString() + "\n";
    }

    static size_t Count()
    {
        return error_list.size();
    }

};

std::ostream &operator<<(std::ostream &os, Error::BasicError const &error);