#pragma once

#include <assert.h>

namespace AST
{
    struct Type
    {
        enum DataType
        {
            UNNOWN, // error case

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
        Type() : type(DataType::UNNOWN) {}
        Type(DataType t) : type(t) {}
        bool operator==(Type t) { return t.type == this->type; }
        bool operator!=(Type t) { return t.type != this->type; }
        bool operator==(DataType t) { return t == this->type; }
        bool operator!=(DataType t) { return t != this->type; }
        operator int() { return type; }

        static Type FromString(std::string s)
        {
            if (s == "BOOL")
                return BOOL;
            if (s == "SINT")
                return SINT;
            if (s == "INT")
                return INT;
            if (s == "DINT")
                return DINT;
            if (s == "LINT")
                return LINT;
            if (s == "USINT")
                return USINT;
            if (s == "UINT")
                return UINT;
            if (s == "UDINT")
                return UDINT;
            if (s == "ULINT")
                return ULINT;
            if (s == "REAL")
                return REAL;
            if (s == "LREAL")
                return LREAL;
            if (s == "TIME")
                return TIME;
            if (s == "LTIME")
                return LTIME;
            if (s == "DATE")
                return DATE;
            if (s == "LDATE")
                return LDATE;
            if (s == "TOD")
                return TOD;
            if (s == "LTOD")
                return LTOD;
            if (s == "DT")
                return DT;
            if (s == "LDT")
                return LDT;
            if (s == "STRING")
                return STRING;
            if (s == "WSTRING")
                return WSTRING;
            if (s == "CHAR")
                return CHAR;
            if (s == "WCHAR")
                return WCHAR;
            if (s == "BYTE")
                return BYTE;
            if (s == "WORD")
                return WORD;
            if (s == "DWORD")
                return DWORD;
            if (s == "LWORD")
                return LWORD;
            return UNNOWN;
        }

        std::string ToString()
        {
            if(type == STRUCT) return "STRUCT"; 
            if(type == ARRAY) return "ARRAY"; 
            if(type == BOOL) return "BOOL"; 
            if(type == SINT) return "SINT"; 
            if(type == INT) return "INT"; 
            if(type == DINT) return "DINT"; 
            if(type == LINT) return "LINT"; 
            if(type == USINT) return "USINT"; 
            if(type == UINT) return "UINT"; 
            if(type == UDINT) return "UDINT"; 
            if(type == ULINT) return "ULINT"; 
            if(type == REAL) return "REAL"; 
            if(type == LREAL) return "LREAL"; 
            if(type == TIME) return "TIME"; 
            if(type == LTIME) return "LTIME"; 
            if(type == DATE) return "DATE"; 
            if(type == LDATE) return "LDATE"; 
            if(type == TOD) return "TOD"; 
            if(type == LTOD) return "LTOD"; 
            if(type == DT) return "DT"; 
            if(type == LDT) return "LDT"; 
            if(type == STRING) return "STRING"; 
            if(type == WSTRING) return "WSTRING"; 
            if(type == CHAR) return "CHAR"; 
            if(type == WCHAR) return "WCHAR"; 
            if(type == BYTE) return "BYTE"; 
            if(type == WORD) return "WORD"; 
            if(type == DWORD) return "DWORD"; 
            if(type == LWORD) return "LWORD"; 
            return "UNNOWN"; 
        }

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
            return 0; // error case
        }
    };

    
}