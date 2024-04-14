

#include <stdio.h>
#include <inttypes.h>
#include <iostream>

#ifndef PLC_DATA_TYPES
#define PLC_DATA_TYPES

#define BOOL bool
#define SINT uint8_t
#define INT int16_t
#define DINT int32_t
#define LINT int64_t
#define USINT int8_t
#define UINT uint16_t
#define UDINT uint32_t
#define ULINT uint64_t
#define REAL float
#define LREAL double

#endif

extern "C" void test_func(INT aaa, INT b, INT c1, REAL *b1, INT *x, BOOL *test_func);

int main(void)
{
    INT aaa = 1;
    INT b = 2;
    INT c1 = 3;
    REAL b1 = 0;
    INT x = 0;
    BOOL test_func_result = 0;

    std::cout << "[przed odpaleniem funkcji]\n";
    std::cout << "   INT aaa = " << (int)aaa << "\n";
    std::cout << "   INT b = " << (int)b << "\n";
    std::cout << "   INT c1 = " << (int)c1 << "\n";
    std::cout << "   REAL b1 = " << (REAL)b1 << "\n";
    std::cout << "   INT x = " << (int)x << "\n";
    std::cout << "   BOOL test_func_result = " << (int)test_func_result << "\n";

    for (int i = 0; i < 10; i++)
    {
        test_func(aaa, b, c1, &b1, &x, &test_func_result);

        std::cout << "[i = " << i << "   po odpaleniu]\n";
        std::cout << "   INT aaa = " << (int)aaa << "\n";
        std::cout << "   INT b = " << (int)b << "\n";
        std::cout << "   INT c1 = " << (int)c1 << "\n";
        std::cout << "   REAL b1 = " << (REAL)b1 << "\n";
        std::cout << "   INT x = " << (int)x << "\n";
        std::cout << "   BOOL test_func_result = " << (int)test_func_result << "\n";
    }
}
