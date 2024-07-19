#pragma once

#include <assert.h>

namespace AST
{
    struct Type
    {
        enum DataType
        {
            STRUCT,
            ARRAY,

            BOOL,
            SINT,
            INT,
            DINT,
            LINT,
            USINT,
            UINT,
            UDINT,
            ULINT,
            REAL,
            LREAL,
            TIME,
            LTIME,
            DATE,
            LDATE,
            TOD,
            LTOD,
            DT,
            LDT,
            STRING,
            WSTRING,
            CHAR,
            WCHAR,
            BYTE,
            WORD,
            DWORD,
            LWORD,
        };

    private:
        DataType type;

    public:
        bool operator==(Type t) { return t.type == this->type; }
        bool operator!=(Type t) { return t.type != this->type; }
        operator int() { return type; }

        bool IsUnsignedType()
        {
            switch (type)
            {
            case DataType::BOOL:
            case DataType::BYTE:
            case DataType::WORD:
            case DataType::DWORD:
            case DataType::LWORD:
            case DataType::USINT:
            case DataType::UINT:
            case DataType::UDINT:
            case DataType::ULINT:
                return true;
            default:
                return false;
            }
        }

        bool IsSignedType()
        {
            switch (type)
            {
            case DataType::SINT:
            case DataType::INT:
            case DataType::DINT:
            case DataType::LINT:
            case DataType::REAL:
            case DataType::LREAL:
            case DataType::TIME:
            case DataType::LTIME:
                return true;
            default:
                return false;
            }
        }

        bool IsFloatingPoint()
        {
            switch (type)
            {
            case DataType::REAL:
            case DataType::LREAL:
                return true;
            default:
                return false;
            }
        }

        bool IsSignedInteger()
        {
            switch (type)
            {
            case DataType::LINT:
            case DataType::DINT:
            case DataType::INT:
            case DataType::SINT:
                return true;
            default:
                return false;
            }
        }

        bool IsUnsignedInteger()
        {
            switch (type)
            {
            case DataType::ULINT:
            case DataType::UDINT:
            case DataType::UINT:
            case DataType::USINT:
                return true;
            default:
                return false;
            }
        }

        bool IsInteger()
        {
            return IsSignedInteger() || IsUnsignedInteger();
        }

        bool IsNumeric()
        {
            return IsInteger() || IsFloatingPoint();
        }

        bool IsBit()
        {
            switch (type)
            {
            case DataType::LWORD:
            case DataType::DWORD:
            case DataType::WORD:
            case DataType::BYTE:
            case DataType::BOOL:
                return true;
            default:
                return false;
            }
        }

        // returns size in bits;
        // something like in c: sizeof(T) * 8;
        int GetSize()
        {
            switch (type)
            {
            case DataType::BOOL:
                return 1;
            case DataType::SINT:
            case DataType::USINT:
            case DataType::BYTE:
                return 8;
            case DataType::INT:
            case DataType::UINT:
            case DataType::WORD:
                return 16;
            case DataType::DINT:
            case DataType::UDINT:
            case DataType::DWORD:
            case DataType::REAL:
                return 32;
            case DataType::LINT:
            case DataType::ULINT:
            case DataType::LREAL:
            case DataType::LWORD:
                return 64;
            case DataType::TIME:
            case DataType::LTIME:
            case DataType::DATE:
            case DataType::LDATE:
            case DataType::TOD:
            case DataType::LTOD:
            case DataType::DT:
            case DataType::LDT:
            case DataType::STRING:
            case DataType::WSTRING:
            case DataType::CHAR:
            case DataType::WCHAR:
                assert(false); // todo

            default:
                assert(false);
            }
        }
    };
}