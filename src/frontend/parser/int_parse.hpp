#include <string>
#include <boost/multiprecision/cpp_int.hpp>

typedef boost::multiprecision::cpp_int big_int;

static int CharToNum(char c)
{
    if (c >= '0' && c <= '9')
    {
        return (int)c - (int)'0';
    }

    if (c >= 'a' && c <= 'z')
    {
        return (int)c - (int)'a' + 0x0A;
    }

    if (c >= 'A' && c <= 'Z')
    {
        return (int)c - (int)'A' + 0x0A;
    }

    return -1;
}

bool ParseInteger(const std::string str, int base, big_int *result)
{
    big_int res;
    bool minus = false;
    for (int i = 0; i < str.size(); i++)
    {
        char c = str[i];
        if (i == 0 & c == '+')
        {
            continue;
        }

        if (i == 0 & c == '-')
        {
            minus = true;
            continue;
        }

        int n = CharToNum(c);
        if (n == -1 && n >= base)
        {
            return false;
        }
        res *= base;
        res += n;
    }

    *result = minus ? -res : res;
    return true;
}
