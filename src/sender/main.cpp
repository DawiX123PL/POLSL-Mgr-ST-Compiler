#include <iostream>
#include <fstream>
#include <boost/asio.hpp>
#include "console/command_line_parser.hpp"
#include "data_frame/data_frame.hpp"

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

enum class CommandLineFlags : unsigned int
{
    HELP,
    VERBOSE,
    PLC_ADDRESS,
    PLC_PORT,
    PACKAGE_FILE,
};

void RegisterCommands(CommandLineParser<CommandLineFlags> *command_line)
{
    command_line->RegisterFlag(CommandLineFlags::HELP, 0, {"-h", "--help"});
    command_line->RegisterFlag(CommandLineFlags::VERBOSE, 0, {"-v", "--verbose"});
    command_line->RegisterFlag(CommandLineFlags::PLC_ADDRESS, 1, {"--address"});
    command_line->RegisterFlag(CommandLineFlags::PLC_PORT, 1, {"--port"});
    command_line->RegisterFlag(CommandLineFlags::PACKAGE_FILE, 1, {"-i"});
}

CommandLineParser<CommandLineFlags> ParseCommandLine(int argc, char const *argv[])
{
    CommandLineParser<CommandLineFlags> command_line;
    RegisterCommands(&command_line);
    command_line.Parse(argc, argv);
    return command_line;
}

int main(int argc, char **argv)
{
    CommandLineParser<CommandLineFlags> cli = ParseCommandLine(argc, argv);

    if (!cli.IsFlagUsed(CommandLineFlags::PACKAGE_FILE))
    {
        std::cout << "Error: Missing .package file\n";
        return -1;
    }

    if (cli.GetFlagArgs(CommandLineFlags::PACKAGE_FILE).size() < 1)
    {
        std::cout << "Error: Missing .package file\n";
        return -1;
    }

    std::string package_path = cli.GetFlagArgs(CommandLineFlags::PACKAGE_FILE)[0];
    std::vector<uint8_t> package_file_content;

    if (!ReadFile(package_path, &package_file_content))
    {
        std::cout << "Error: Cannot open file: " << package_path << "\n";
        return -1;
    }

    boost::asio::io_context io_context;
    boost::asio::ip::tcp::resolver resolver(io_context);

    if (!cli.IsFlagUsed(CommandLineFlags::PLC_ADDRESS))
    {
        std::cout << "Missing address of PLC device \n";
        return -1;
    }

    if (cli.GetFlagArgs(CommandLineFlags::PLC_ADDRESS).size() < 1)
    {
        std::cout << "Missing address of PLC device \n";
        return -1;
    }

    boost::system::error_code ec;
    auto address = boost::asio::ip::make_address_v4(cli.GetFlagArgs(CommandLineFlags::PLC_ADDRESS)[0], ec);

    if (ec)
    {
        std::cout << "Invalid devide address \n";
        return -1;
    }

    uint32_t port = 2000;

    if (cli.IsFlagUsed(CommandLineFlags::PLC_PORT))
    {
        if (cli.GetFlagArgs(CommandLineFlags::PLC_PORT).size() >= 1)
        {
            port = std::stoll(cli.GetFlagArgs(CommandLineFlags::PLC_PORT)[0]);
        }
    }

    boost::asio::ip::tcp::endpoint endpoint(address, port);
    boost::asio::ip::tcp::socket socket(io_context);

    socket.connect(endpoint, ec);

    if (ec)
    {
        std::cout << "Unable to connect to devide: " << endpoint << " \n";
        socket.close();
        return -1;
    }

    DataFrame rx_frame;

    int index = 0;
    while (index < package_file_content.size())
    {
        DataFrame tx_frame;
        tx_frame.Push("PROGMEM");
        tx_frame.Push("W");

        uint8_t *begin = &package_file_content[index];
        uint32_t size = std::min(128ull, index - package_file_content.size());

        tx_frame.PushHex(begin, size);

        index += size;

        // send tcp package
        socket.write_some(ec);
        if (ec)
        {
            std::cout << "Device disconnected \n";
            socket.close();
            return -1;
        }

        // wait for response
        // {
        //     uint8_t buffer[128];
        //     uint32_t rx_byte_count = socket.read_some(buffer, ec);
        //     for (int i = 0; i < rx_byte_count; i++)
        //     {
        //         rx_frame.BufferPush(buffer[i]);
        //         if(buffer[i]){

        //         }
        //     }
        // }
    }

    std::cout << "Successfuly sended package file \n";
    socket.close();
}
