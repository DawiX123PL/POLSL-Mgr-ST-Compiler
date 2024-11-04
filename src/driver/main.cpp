#include "console/command_line_parser.hpp"

#include <vector>
#include <string>
#include <filesystem>
#include <cstdlib>

enum class CommandLineFlags : unsigned int
{
    HELP,
    OUTPUT_FILE,
    VERBOSE,
    OUTPUT_C_HEADER,
    TARGET_TRIPLE,
    EMIT_LL_WITH_ERRORS,
    MODULES,
    ENTRY_POINT,
};

void RegisterCommands(CommandLineParser<CommandLineFlags> *command_line)
{
    command_line->RegisterFlag(CommandLineFlags::HELP, 0, {"-h", "--help"});
    command_line->RegisterFlag(CommandLineFlags::OUTPUT_FILE, 1, {"-o"});
    command_line->RegisterFlag(CommandLineFlags::VERBOSE, 0, {"-v", "--verbose"});
    command_line->RegisterFlag(CommandLineFlags::OUTPUT_C_HEADER, 1, {"--output-c-header"});
    command_line->RegisterFlag(CommandLineFlags::TARGET_TRIPLE, 1, {"-target"});
    command_line->RegisterFlag(CommandLineFlags::EMIT_LL_WITH_ERRORS, 0, {"--emit_ll_with_errors"});
    command_line->RegisterFlag(CommandLineFlags::MODULES, 0, {"-modules"});
    command_line->RegisterFlag(CommandLineFlags::ENTRY_POINT, 1, {"--entry_point"});
}

CommandLineParser<CommandLineFlags> ParseCommandLine(int argc, char const *argv[])
{
    CommandLineParser<CommandLineFlags> command_line;
    RegisterCommands(&command_line);
    command_line.Parse(argc, argv);
    return command_line;
}

template <typename T>
void GetArgument(CommandLineParser<CommandLineFlags> &cli, T *data, CommandLineFlags flag)
{
    if (cli.IsFlagUsed(flag))
    {
        if (cli.GetFlagArgs(flag).size() >= 1)
        {
            *data = cli.GetFlagArgs(flag)[0];
        }
    }
}

int Execute(std::string command, const std::vector<std::string> &args)
{
    std::string cmd = command;
    for (auto arg : args)
    {
        cmd += " " + arg;
    }

    return std::system(cmd.c_str());
}

int main(int argc, const char **argv)
{
    CommandLineParser<CommandLineFlags> cli = ParseCommandLine(argc, argv);

    // output file name
    std::filesystem::path output_file = "output.package";
    GetArgument(cli, &output_file, CommandLineFlags::OUTPUT_FILE);

    std::string target_triple = "thumbv7em-none-unknown-eabi";
    GetArgument(cli, &output_file, CommandLineFlags::TARGET_TRIPLE);

    // std::string modules_path = "plc_modules.modules";
    // GetArgument(cli, &modules_path, CommandLineFlags::MODULES);

    std::filesystem::path sysroot = std::filesystem::path(cli.GetSelfPath()).parent_path().parent_path();
    std::filesystem::path bin = sysroot / "bin";

    std::string arch = "-march=armv7e-m+fp";
    std::string cpu = "-mcpu=cortex-m4";
    std::string fpu = "-mfpu=fpv4-sp-d16";
    // std::string float_abi = "-mfloat-abi=soft";
    std::string float_abi = "-mfloat-abi=hard";
    std::string linker_script = (sysroot / "ld/plc_default.ld").string();

    std::string lib_path = "-L" + (sysroot / "lib/thumbv7e-m+fp").string();
    std::vector<std::string> libs = {"-lgcc", "-lc", "-lnosys", "-lm"};

    std::vector<std::string> default_st_files = {(sysroot / "stl/conv.st_extern").string()};
    std::vector<std::string> default_c_files = {(sysroot / "stl/conv.c").string()};

    // get st flags
    std::vector<std::string> st_flags = {"-target",
                                         target_triple};

    std::vector<std::string> clang_flags = {"-nostdlib",
                                            "-target",
                                            target_triple,
                                            "-fPIC",
                                            arch,
                                            cpu,
                                            fpu,
                                            float_abi,
                                            linker_script,
                                            "-mthumb",
                                            lib_path};

    clang_flags.insert(clang_flags.end(), libs.begin(), libs.end());
    clang_flags.insert(clang_flags.end(), default_c_files.begin(), default_c_files.end());
    st_flags.insert(st_flags.end(), default_st_files.begin(), default_st_files.end());

    for (auto flag : cli.GetFiles())
    {
        // if flag or file
        bool is_flag = flag.rfind("-", 0) == 0;

        if (is_flag)
        {
            clang_flags.push_back(flag);
            continue;
        }

        // check if st or c++ file
        std::filesystem::path file = flag;
        if (file.extension() == ".st" || file.extension() == ".st_extern")
        {
            st_flags.push_back(flag);
        }
        else
        {
            clang_flags.push_back(flag);
        }
    }

    st_flags.push_back("-o");
    st_flags.push_back(output_file.replace_extension(".ll").string());    // st-frontend output
    clang_flags.push_back(output_file.replace_extension(".ll").string()); // clang output
    clang_flags.push_back("-o");
    clang_flags.push_back(output_file.replace_extension(".elf").string()); // clang output

    std::vector<std::string> obj_copy_flags = {"-O",
                                               "binary",
                                               output_file.replace_extension(".elf").string(),
                                               output_file.replace_extension(".bin").string()};

    std::vector<std::string> packager_flags = {
        // "-modules",
        // modules_path,
        "-bin",
        output_file.replace_extension(".bin").string(),
        "-o",
        output_file.replace_extension(".package").string()};

    // execute programs

    int exit_code;

    exit_code = Execute((bin / "st_frontend").string(), st_flags);
    if (exit_code != 0)
    {
        return exit_code;
    }

    exit_code = Execute("clang", clang_flags);
    if (exit_code != 0)
    {
        return exit_code;
    }

    exit_code = Execute("llvm-objcopy", obj_copy_flags);
    if (exit_code != 0)
    {
        return exit_code;
    }

    exit_code = Execute((bin / "packager").string(), packager_flags);
    if (exit_code != 0)
    {
        return exit_code;
    }

    return 0;
}
