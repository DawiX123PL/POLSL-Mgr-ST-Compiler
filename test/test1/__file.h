#pragma once

#ifndef PLC_DATA_TYPES
#define PLC_DATA_TYPES

#define BOOL     uint8_t
#define SINT     uint8_t
#define INT      int16_t
#define DINT     int32_t
#define LINT     int64_t
#define USINT    int8_t
#define UINT     uint16_t
#define UDINT    uint32_t
#define ULINT    uint64_t
#define REAL     float
#define LREAL    double

#endif

void test_func( SINT aaa, SINT b, SINT c1, SINT* b1, SINT* x, SINT* test_func);

