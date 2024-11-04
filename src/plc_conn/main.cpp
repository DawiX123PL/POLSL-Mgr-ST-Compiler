#include "file_utils.hpp"
#include "console/command_line_parser.hpp"
#include "console/color.hpp"
#include <boost/asio.hpp>
#include "tcp_utils.hpp"

#define CONN_INFO_VERBOSE(cli, info)                                             \
    {                                                                            \
        if (cli.IsFlagUsed(CommandLineFlags::VERBOSE))                           \
        {                                                                        \
            std::cout << Console::FgBrightCyan("[INFO]") << " " << info << "\n"; \
        }                                                                        \
    }

#define CONN_INFO(info)                                                      \
    {                                                                        \
        std::cout << Console::FgBrightCyan("[INFO]") << " " << info << "\n"; \
    }

#define CONN_PLC_RESPONSE(info)                                                      \
    {                                                                                \
        std::cout << Console::FgBrightCyan("[PLC_RESPONSE]") << " " << info << "\n"; \
    }

#define CONN_ERROR(error)                                                     \
    {                                                                         \
        std::cout << Console::FgBrightRed("[ERROR]") << " " << error << "\n"; \
        std::cout.flush();                                                    \
        return -1;                                                            \
    }

#define CONN_CHECK_IF_FLAG_USED(cli, flag, error_message) \
    {                                                     \
        if (!cli.IsFlagUsed(flag))                        \
        {                                                 \
            CONN_ERROR(error_message)                     \
        }                                                 \
    }

#define CONN_CHECK_IF_FLAG_USED_WITH_ARG(cli, flag, error_message) \
    {                                                              \
        if (!cli.IsFlagUsed(flag))                                 \
        {                                                          \
            CONN_ERROR(error_message)                              \
        }                                                          \
    }

#define CONN_CHECK_ERROR(err)         \
    {                                 \
        if (err)                      \
        {                             \
            CONN_ERROR(err.message()) \
        }                             \
    }

#define CONN_CHECK_RESPONSE(command_frame, response_frame)                           \
    {                                                                                \
        if (!IsResponseOk(response_frame, command_frame[0].Get<std::string_view>())) \
        {                                                                            \
            CONN_ERROR("Unexpected response" << response_frame.BufferGet())          \
            return -1;                                                               \
        }                                                                            \
    }

#define CONN_CHECK_FILE_COUNT(cli)                \
    {                                             \
        if (cli.GetFiles().size() != 1)           \
        {                                         \
            CONN_ERROR("Expected One input File") \
        }                                         \
    }

enum class CommandLineFlags : unsigned int
{
    HELP,
    VERBOSE,
    PLC_ADDRESS,
    PLC_PORT,
    UPLOAD_FILE,
    START,
    STOP,
    VERIFY,
    PERFORMANCE,
};

void RegisterCommands(CommandLineParser<CommandLineFlags> *command_line)
{
    command_line->RegisterFlag(CommandLineFlags::HELP, 0, {"-h", "--help"});
    command_line->RegisterFlag(CommandLineFlags::VERBOSE, 0, {"-v", "--verbose"});
    command_line->RegisterFlag(CommandLineFlags::PLC_ADDRESS, 1, {"--address"});
    command_line->RegisterFlag(CommandLineFlags::PLC_PORT, 1, {"--port"});
    command_line->RegisterFlag(CommandLineFlags::UPLOAD_FILE, 0, {"--upload"});
    command_line->RegisterFlag(CommandLineFlags::START, 0, {"--start"});
    command_line->RegisterFlag(CommandLineFlags::STOP, 0, {"--stop"});
    command_line->RegisterFlag(CommandLineFlags::VERIFY, 0, {"--verify"});
    command_line->RegisterFlag(CommandLineFlags::PERFORMANCE, 0, {"--performance"});
}

CommandLineParser<CommandLineFlags> ParseCommandLine(int argc, char const *argv[])
{
    CommandLineParser<CommandLineFlags> command_line;
    RegisterCommands(&command_line);
    command_line.Parse(argc, argv);
    return command_line;
}

int main(int argc, char const *argv[])
{
    setlocale(LC_ALL, "");

    CommandLineParser<CommandLineFlags> cli = ParseCommandLine(argc, argv);

    boost::asio::io_context io_context;
    boost::asio::ip::tcp::resolver resolver(io_context);

    CONN_CHECK_IF_FLAG_USED_WITH_ARG(cli, CommandLineFlags::PLC_ADDRESS, "Missing address of PLC device");
    CONN_CHECK_IF_FLAG_USED_WITH_ARG(cli, CommandLineFlags::PLC_PORT, "Missing port of PLC device");

    std::string address_str = cli.GetFlagArgs(CommandLineFlags::PLC_ADDRESS)[0];
    uint32_t port = std::stoll(cli.GetFlagArgs(CommandLineFlags::PLC_PORT)[0]);

    boost::system::error_code ec;
    auto address = boost::asio::ip::make_address_v4(address_str, ec);
    CONN_CHECK_ERROR(ec);

    boost::asio::ip::tcp::endpoint endpoint(address, port);
    boost::asio::ip::tcp::socket socket(io_context);

    CONN_INFO_VERBOSE(cli, "Connecting to: " << endpoint);
    socket.connect(endpoint, ec);
    CONN_CHECK_ERROR(ec);

    CONN_INFO_VERBOSE(cli, "Connected");

    if (cli.IsFlagUsed(CommandLineFlags::STOP))
    {
        CONN_INFO_VERBOSE(cli, "Stopping PLC");

        const DataFrame cmd = CreateCommand("STOP");
        DataFrame resp = WriteAndWaitForResponse(socket, cmd, ec);

        CONN_CHECK_ERROR(ec);
        CONN_CHECK_RESPONSE(cmd, resp);
    }

    if (cli.IsFlagUsed(CommandLineFlags::UPLOAD_FILE))
    {
        CONN_CHECK_FILE_COUNT(cli);

        std::string package_path = cli.GetFiles()[0];
        std::vector<uint8_t> package_file_content;
        if (!ReadFile(package_path, &package_file_content))
        {
            CONN_ERROR("Cannot open file: " << package_path)
        }

        CONN_INFO_VERBOSE(cli, "Upload file");

        int mem_address = 0;
        while (mem_address < package_file_content.size())
        {
            uint8_t *begin = &package_file_content[mem_address];
            uint32_t size = std::min(128ull, mem_address - package_file_content.size());

            DataFrame cmd = CreateCommand("PROGMEM", "W", mem_address);
            cmd.PushHex(begin, size);

            mem_address += size;

            DataFrame resp = WriteAndWaitForResponse(socket, cmd, ec);

            CONN_CHECK_ERROR(ec);
            CONN_CHECK_RESPONSE(cmd, resp);
        }
    }

    if (cli.IsFlagUsed(CommandLineFlags::VERIFY) || cli.IsFlagUsed(CommandLineFlags::UPLOAD_FILE))
    {
        CONN_INFO_VERBOSE(cli, "Verifying");

        DataFrame cmd = CreateCommand("PROGMEM", "VERIFY");
        DataFrame resp = WriteAndWaitForResponse(socket, cmd, ec);

        CONN_CHECK_ERROR(ec);
        CONN_CHECK_RESPONSE(cmd, resp);
    }

    if (cli.IsFlagUsed(CommandLineFlags::START))
    {
        CONN_INFO_VERBOSE(cli, "Starting PLC");

        DataFrame cmd = CreateCommand("START");
        DataFrame resp = WriteAndWaitForResponse(socket, cmd, ec);

        CONN_CHECK_ERROR(ec);
        CONN_CHECK_RESPONSE(cmd, resp);
    }

    if (cli.IsFlagUsed(CommandLineFlags::PERFORMANCE))
    {
        CONN_INFO_VERBOSE(cli, "Reading plc performance");

        DataFrame cmd = CreateCommand("PERFORMANCE");
        DataFrame resp = WriteAndWaitForResponse(socket, cmd, ec);

        CONN_CHECK_ERROR(ec);
        CONN_CHECK_RESPONSE(cmd, resp);

        for (int i = 2; i < resp.Size(); i++)
        {
            CONN_PLC_RESPONSE(resp[i].Get<std::string_view>());
        }
    }

    CONN_INFO_VERBOSE(cli, "Disconnecting");
    socket.close(ec);
    CONN_CHECK_ERROR(ec);

    return 0;
}
