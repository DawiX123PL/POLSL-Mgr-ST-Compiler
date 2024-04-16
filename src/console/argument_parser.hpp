#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>

class ArgumentParser
{

public:
    enum class Flags
    {
        Verbose,
        Help,
        Version,
        Output,
        OutputCHeader,
    };

private:
    const std::map<std::string, Flags> flags_string_map = {
        {"-v", Flags::Verbose},
        {"--verbose", Flags::Verbose},
        {"-h", Flags::Help},
        {"--help", Flags::Help},
        {"--version", Flags::Version},
        {"-o", Flags::Output},
        {"--output-c-header", Flags::OutputCHeader}};

    // key: input flag (string)
    // value: number of arguments (integer)
    const std::map<Flags, int> flags_argument_count = {
        {Flags::Verbose, 0},
        {Flags::Help, 0},
        {Flags::Version, 0},
        {Flags::Output, 1},
        {Flags::OutputCHeader, 1}};

    // key: flag
    std::map<Flags, std::string> flag_list;
    std::vector<std::string> free_arguments_list;
    std::string exec_path;

public:
    std::vector<std::string> ArgsToStrList(int argc, char **argv)
    {
        std::vector<std::string> list;
        for (int i = 0; i < argc; i++)
        {
            list.emplace_back(argv[i]);
        }
        return list;
    }

    void Parse(int argc, char **argv)
    {
        Parse(ArgsToStrList(argc, argv));
    }

    void Parse(std::vector<std::string> arg_str_list)
    {
        if (arg_str_list.size() >= 1)
        {
            exec_path = arg_str_list.front();
        }

        Flags flag;
        int arg_count = 0;
        for (int i = 1; i < arg_str_list.size(); i++)
        {
            std::string arg_str = arg_str_list[i];

            if (arg_count > 0)
            {
                arg_count--;
                flag_list[flag] = arg_str;
                continue;
            }

            // step 1 - check if argument is flag.
            auto arg_iter = flags_string_map.find(arg_str);
            if (arg_iter == flags_string_map.end())
            {
                free_arguments_list.push_back(arg_str);
                continue;
            }

            flag = arg_iter->second;
            arg_count = flags_argument_count.at(flag);
            flag_list[flag] = "";
        }
    }

    const std::vector<std::string> &GetFreeArguments()
    {
        return free_arguments_list;
    }

    const std::map<Flags, std::string> &GetFlags()
    {
        return flag_list;
    }

    const std::string &GetExecPath()
    {
        return exec_path;
    }

    bool HaveFlag(Flags flag)
    {
        auto arg_iter = flag_list.find(flag);
        bool have_flag = arg_iter != flag_list.end();
        return have_flag;
    }
};