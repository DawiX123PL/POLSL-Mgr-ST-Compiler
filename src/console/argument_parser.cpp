#include "argument_parser.hpp"



const char* ArgFlagToStr(ArgFlag flag){
    switch(flag){
        case ArgFlag::Help:     return "Help";
        case ArgFlag::Verbose:  return "Verbose";
        case ArgFlag::FilePath: return "FilePath";
    }
    return "";
}

std::vector<std::string> ArgsToStrList(int argc, char **argv)
{
    std::vector<std::string> list;
    for (int i = 0; i < argc; i++)
    {
        list.emplace_back(argv[i]);
    }
    return list;
}

std::map<ArgFlag, std::string> ArgsToMap(int argc, char **argv)
{
    const std::vector<std::string> arg_list = ArgsToStrList(argc, argv);

    std::map<ArgFlag, std::string> arg_map;

    for (int i = 0; i < arg_list.size(); i++)
    {
        const std::string &arg = arg_list[i];

        if (arg == "-v" || arg == "--verbose")
        {
            arg_map[ArgFlag::Verbose] = "true";
            continue;
        }

        if (arg == "-h" || arg == "--help")
        {
            arg_map[ArgFlag::Help] = "true";
            continue;
        }

        if (arg == "-f" || arg == "--file")
        {
            arg_map[ArgFlag::FilePath] = "";

            if (i + 1 < arg_list.size())
            {
                arg_map[ArgFlag::FilePath] = arg_list[i + 1];
            }

            continue;
        }
    }

    return arg_map;
};

void PrintArgs(const std::map<ArgFlag, std::string> &args)
{
    for(auto iter = args.begin(); iter != args.end(); iter++){
        std::cout << "Input Flag: " << ArgFlagToStr(iter->first) << " :\t " << iter->second << "\n"; 
    }
}

bool IsArgsContain(const std::map<ArgFlag, std::string>& args, ArgFlag flag)
{
    auto flag_pos = args.find(flag);
    return flag_pos != args.end();
}