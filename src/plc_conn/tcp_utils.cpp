#include "tcp_utils.hpp"

DataFrame ReadFrame(boost::asio::ip::tcp::socket &socket, boost::system::error_code &ec)
{

    boost::asio::streambuf buffer;
    boost::asio::read_until(socket, buffer, '\n', ec);

    // boost::asio::async_read_until()
    DataFrame rx_frame;
    rx_frame.Clear();

    if (ec)
    {
        return rx_frame;
    }

    std::istream is(&buffer);
    std::string line;
    std::getline(is, line);

    for (char c : line)
    {
        rx_frame.BufferPush(c);
    }
    rx_frame.BufferPush('\n');

    rx_frame.Parse();
    return rx_frame;
}

void WriteFrame(boost::asio::ip::tcp::socket &socket, DataFrame data_frame, boost::system::error_code &ec)
{
    socket.write_some(boost::asio::buffer(data_frame.BufferGet()), ec);
}

DataFrame WriteAndWaitForResponse(boost::asio::ip::tcp::socket &socket, DataFrame data_frame, boost::system::error_code &ec)
{
    WriteFrame(socket, data_frame, ec);

    if (ec)
    {
        return DataFrame{};
    }

    DataFrame response = ReadFrame(socket, ec);
    return response;
}

// return true if OK
bool IsResponseOk(DataFrame& frame, std::string_view command)
{
    if(frame.Size() < 2)
    {
        return false;
    }

    if(frame[0].Get<std::string_view>() != command)
    {
        return false;
    }

    if(frame[1].Get<std::string_view>() != "OK")
    {
        return false;
    }

    return true;
}