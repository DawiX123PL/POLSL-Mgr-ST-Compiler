#pragma once

#include <boost/asio.hpp>
#include "data_frame/data_frame.hpp"

DataFrame ReadFrame(boost::asio::ip::tcp::socket &socket, boost::system::error_code &ec);
void WriteFrame(boost::asio::ip::tcp::socket &socket, DataFrame data_frame, boost::system::error_code &ec);
DataFrame WriteAndWaitForResponse(boost::asio::ip::tcp::socket &socket, DataFrame data_frame, boost::system::error_code &ec);

template <class T1>
DataFrame CreateCommand(T1 v1)
{
    DataFrame frame;
    frame.Push(v1);
    frame.Parse();
    return frame;
}

template <class T1, class T2>
DataFrame CreateCommand(T1 v1, T2 v2)
{
    DataFrame frame;
    frame.Push(v1);
    frame.Push(v2);
    frame.Parse();
    return frame;
}

template <class T1, class T2, class T3>
DataFrame CreateCommand(T1 v1, T2 v2, T3 v3)
{
    DataFrame frame;
    frame.Push(v1);
    frame.Push(v2);
    frame.Push(v3);
    frame.Parse();
    return frame;
}

// return true if OK
bool IsResponseOk(DataFrame &frame, std::string_view command);
