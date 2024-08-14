#include <iostream>
#include <fstream>
#include <boost/crc.hpp>
#include "console/command_line_parser.hpp"

extern "C"
{
    constexpr uint32_t user_code_bin_size = 20 * 1024; // program memory - 20kB
    constexpr uint32_t modules_count = 64;             // program memory - 20kB

    typedef void (*ProgramPtr)(void *);
    typedef void (*ProgramInitPtr)(void *);

    // struct containing pointers to executable functions and program size
    struct SymbolTable
    {
        ProgramPtr program;
        ProgramInitPtr program_init;
        uint32_t program_size;
    };

    struct CodeBlockData
    {
        // info about physical modules required by user code
        uint8_t required_modules[modules_count] = {};

        // executable code
        uint8_t executable_code[user_code_bin_size] = {};
    };

    struct CodeBlock
    {
        uint32_t crc; // to verify user code integrity;
        CodeBlockData code;
    };
}

enum class CommandLineFlags : unsigned int
{
    HELP,
    OUTPUT_FILE,
    INPUT_EXECUTABLE,
    INPUT_MODULE_CONFIG,
    VERBOSE,
};

void RegisterCommands(CommandLineParser<CommandLineFlags> *command_line)
{
    command_line->RegisterFlag(CommandLineFlags::HELP, 0, {"-h", "--help"});
    command_line->RegisterFlag(CommandLineFlags::OUTPUT_FILE, 1, {"-o"});
    command_line->RegisterFlag(CommandLineFlags::VERBOSE, 0, {"-v", "--verbose"});
    command_line->RegisterFlag(CommandLineFlags::INPUT_EXECUTABLE, 1, {"-bin"});
    command_line->RegisterFlag(CommandLineFlags::INPUT_MODULE_CONFIG, 1, {"-modules"});
}

CommandLineParser<CommandLineFlags> ParseCommandLine(int argc, char const *argv[])
{
    CommandLineParser<CommandLineFlags> command_line;
    RegisterCommands(&command_line);
    command_line.Parse(argc, argv);
    return command_line;
}

uint32_t Crc32CalculateSoft(uint8_t *data, uint32_t size)
{
    constexpr uint32_t bytes = 32;
    constexpr uint32_t polynomial = 0x4C11DB7;
    constexpr uint32_t init_val = 0xFFFFFFFF;
    constexpr uint32_t final_xor = 0x0;
    constexpr bool input_reflected  = false;
    constexpr bool output_reflected = false;

    boost::crc_optimal<bytes, polynomial, init_val, final_xor, input_reflected, output_reflected> crc;

    crc.process_bytes(data, size);

    uint32_t checksum = crc.checksum();

    return checksum;
}

bool ReadFile(std::string file_name, std::vector<uint8_t> *content)
{
    try
    {
        std::fstream file(file_name, std::ios::in | std::ios::binary);

        if (!file.good())
        {
            return false;
        }

        file.seekg(0, file.end);
        int file_length = file.tellg();
        file.seekg(0, file.beg);

        content->resize(file_length);
        auto begin = &*content->begin();
        file.read((char *)begin, content->size());

        file.close();

        return true;
    }
    catch (...)
    {
        return false;
    }

    return true;
}

static bool WriteFile(std::string file_name, uint8_t *file_content, uint32_t file_size)
{
    try
    {
        std::fstream file(file_name, std::ios::out | std::ios::binary);

        if (!file.good())
        {
            return false;
        }

        file.write((char *)file_content, file_size);
        file.close();

        return true;
    }
    catch (...)
    {
        return false;
    }

    return true;
}

int main(int argc, const char *argv[])
{
    CommandLineParser<CommandLineFlags> cli = ParseCommandLine(argc, argv);

    CodeBlock block;

    if (!cli.IsFlagUsed(CommandLineFlags::INPUT_EXECUTABLE))
    {
        std::cout << "Error: missing input binary file\n";
        return -1;
    }

    if (cli.GetFlagArgs(CommandLineFlags::INPUT_EXECUTABLE).size() < 1)
    {
        std::cout << "Error: missing input binary file\n";
        return -1;
    }

    if (!cli.IsFlagUsed(CommandLineFlags::INPUT_MODULE_CONFIG))
    {
        std::cout << "Error: missing module configuration file\n";
        return -1;
    }

    if (cli.GetFlagArgs(CommandLineFlags::INPUT_MODULE_CONFIG).size() < 1)
    {
        std::cout << "Error: missing module configuration file\n";
        return -1;
    }

    std::string module_config_path = cli.GetFlagArgs(CommandLineFlags::INPUT_MODULE_CONFIG)[0];
    std::string input_executable_path = cli.GetFlagArgs(CommandLineFlags::INPUT_EXECUTABLE)[0];
    std::string output_package_path = "./output.package";

    if (!cli.IsFlagUsed(CommandLineFlags::OUTPUT_FILE))
    {
        if (cli.GetFlagArgs(CommandLineFlags::OUTPUT_FILE).size() >= 1)
        {
            output_package_path = cli.GetFlagArgs(CommandLineFlags::OUTPUT_FILE)[0];
        }
    }

    // read file content
    std::vector<uint8_t> module_config;
    std::vector<uint8_t> input_executable;

    if (!ReadFile(module_config_path, &module_config))
    {
        std::cout << "Error: Cannot open file: " << module_config_path << "\n";
        return -1;
    }

    if (!ReadFile(input_executable_path, &input_executable))
    {
        std::cout << "Error: Cannot open file: " << input_executable_path << "\n";
        return -1;
    }

    if (input_executable.size() > user_code_bin_size)
    {
        std::cout << "Executable to big: \n";
        return -1;
    }

    if (module_config_path.size() > modules_count)
    {
        std::cout << "Modules config to big: \n";
        return -1;
    }

    // fill infor about required modules
    for (int i = 0; i < modules_count; i++)
    {
        if (i < module_config.size())
        {
            block.code.required_modules[i] = module_config[i];
        }
        else
        {
            block.code.required_modules[i] = 0;
        }
    }

    // clear user program
    for (int i = 0; i < user_code_bin_size; i++)
    {
        if (i < input_executable.size())
        {
            block.code.executable_code[i] = input_executable[i];
        }
        else
        {
            block.code.executable_code[i] = 0;
        }
    }

    // calculate crc
    block.crc = Crc32CalculateSoft((uint8_t *)&block.code, sizeof(block.code));

    if (!WriteFile(output_package_path, (uint8_t *)&block, sizeof(block)))
    {
        std::cout << "Error: Cannot open file: " << output_package_path << "\n";
        return -1;
    }
}
