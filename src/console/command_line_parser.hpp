#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <string>
#include <vector>
#include <initializer_list>
#include <map>

template <class CommandLineFlags>
class CommandLineParser
{

    // command line arguments not related to any flag
    std::vector<std::string> files;

    // typedef unsigned int FlagID_t;

    // first: flag string (-o -h --help itp.)
    // second: flag id
    std::map<std::string, CommandLineFlags> registered_flags;

    // first: flag id
    // second: argument count
    std::map<CommandLineFlags, unsigned int> registered_arg_count;

    // arguments read from command line
    std::map<CommandLineFlags, std::vector<std::string>> used_flags_with_arguments;

    std::string this_executable_path;

    std::vector<std::string> ArgsToVec(int argc, char const *argv[])
    {
        std::vector<std::string> args;
        for (int i = 0; i < argc; i++)
        {
            args.push_back(argv[i]);
        }
        return args;
    }

public:
    void RegisterFlag(CommandLineFlags flag_id, unsigned int arg_count, std::string arg)
    {
        registered_flags[arg] = flag_id;
        registered_arg_count[flag_id] = arg_count;
    }

    void RegisterFlag(CommandLineFlags flag_id, unsigned int arg_count, std::initializer_list<std::string> args)
    {
        for (auto arg : args)
        {
            registered_flags[arg] = flag_id;
        }

        registered_arg_count[flag_id] = arg_count;
    }

    void Parse(int argc, char const *argv[])
    {
        std::vector<std::string> args_vec = ArgsToVec(argc, argv);

        this_executable_path = args_vec.front();

        int cmd_str_number = 1;
        for (/*nope*/; cmd_str_number < args_vec.size(); cmd_str_number++)
        {
            auto flag_iter = registered_flags.find(args_vec[cmd_str_number]);

            // check if flag is not registered
            if (flag_iter == registered_flags.end())
            {
                files.push_back(args_vec[cmd_str_number]);
                continue;
            }
            else
            {
                CommandLineFlags flag_id = flag_iter->second;

                int arg_count = registered_arg_count[flag_id];
                std::vector<std::string> flag_arguments = {};

                for (int arg_nr = 0; arg_nr < arg_count; arg_nr++)
                {
                    int index = cmd_str_number + arg_nr + 1;
                    if (index < args_vec.size())
                    {
                        flag_arguments.push_back(args_vec[index]);
                    }
                }

                used_flags_with_arguments[flag_id] = flag_arguments;

                cmd_str_number += arg_count;
            }
        }
    }

    bool IsFlagUsed(std::string flag_str)
    {
        auto reg_flag_iter = registered_flags.find(flag_str);
        if (reg_flag_iter == registered_flags.end())
        {
            return false;
        }
        CommandLineFlags flag_id = reg_flag_iter->second;

        auto flag_iter = used_flags_with_arguments.find(flag_id);
        if (flag_iter == used_flags_with_arguments.end())
        {
            return false;
        }

        return true;
    }

    bool IsFlagUsed(CommandLineFlags flag_id)
    {
        auto flag_iter = used_flags_with_arguments.find(flag_id);
        if (flag_iter == used_flags_with_arguments.end())
        {
            return false;
        }

        return true;
    }

    bool IsFlagStringUsed(std::string flag_str)
    {
        auto reg_flag_iter = registered_flags.find(flag_str);
        if (reg_flag_iter == registered_flags.end())
        {
            return false;
        }
        CommandLineFlags flag_id = reg_flag_iter->second;

        auto flag_iter = used_flags_with_arguments.find(flag_id);
        if (flag_iter == used_flags_with_arguments.end())
        {
            return false;
        }

        return true;
    }

    std::vector<std::string> GetFlagArgs(CommandLineFlags flag_id)
    {
        auto flag_iter = used_flags_with_arguments.find(flag_id);
        if (flag_iter == used_flags_with_arguments.end())
        {
            return {};
        }

        return flag_iter->second;
    }

    std::vector<std::string> GetFiles()
    {
        return files;
    }
};
