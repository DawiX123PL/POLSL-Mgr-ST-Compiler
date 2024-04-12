iec:2013

# 6.1.3 Keywords
Keywords are unique combinations of characters utilized as individual syntactic elements. 
**Keywords shall not contain embedded spaces**. 
**The case of characters shall not be significant in keywords**; 
for instance, the keywords `FOR` and `for` are syntactically equivalent. 
They shall **not be used for any other purpose**, for example, variable names or extensions.


# 6.1.4 Use of white space
The user shall be allowed to insert one or more characters of "white space" anywhere in the text of programmable controller programs **except within keywords**, **literals**, **enumerated values**, **identifiers**, **directly represented variables** or **delimiter combinations** for example, for comments. 
**"White space"** is defined as the SPACE character with encoded value 32 decimal, as well as non-printing characters such as tab, newline, etc. for which no encoding is given in IEC/ISO 10646.


# 6.1.5 Comments

1. Single line comments  `//` 
(`(*` and `*)` or `/*` and `*/` have no special meaning.)
2. Multi-line comments `(* comment *)`  `/* comment */`
(`//` has no special meaning.)

Nested comments are possible

Comments shall be permitted anywhere in the program where spaces are allowed, **except within character string literals**.

# 6.2 Pragma
```
{VERSION 2.0}
{AUTHOR JHC}
{x:= 256, y:= 384}
```

# 6.3 Literals

1. Integer `-12, 0; 123_4; +986`
1. Real `0.0; 0.23213; 3.123_323`
1. Real with exponent `-1.32E-12; -1.32e-12; 1.0E+6; 1.0e+6; 1.0E6; 1.0e6`
1. Binary `2#1111_1111; 2#1000_1111`
1. Octal `8#377; 8#340`
1. Hexadecimal `16#ff; 16#FF; 16#E0; 16#e0`
1. Bolean `0; 1` or `FALSE, TRUE`
1. Typed Literal `INT#-123; WORD#16#7FF; BOOL#1; CHAR#16#41`
1. String literals : section 6.3.3
1. Duration Literal : section 6.3.4


# 6.4.2 Data types


| Typ danych PLC            | Typ danych C/C++ | Ze znakiem | Rozmiar (bity) |
| ------------------------- | ---------------- | ---------- | -------------- |
| `BOOL`                    | `bool`           | -          | 1              |
| `SINT`                    | `int8_t`         | Signed     | 8              |
| `INT`                     | `int16_t`        | Signed     | 16             |
| `DINT`                    | `int32_t`        | Signed     | 32             |
| `LINT`                    | `int64_t`        | Signed     | 64             |
| `USINT`                   | `uint8_t`        | Unsigned   | 8              |
| `UINT`                    | `uint16_t`       | Unsigned   | 16             |
| `UDINT`                   | `uint32_t`       | Unsigned   | 32             |
| `ULINT`                   | `uint64_t`       | Unsigned   | 64             |
| `REAL`                    | `float`          | -          | 32             |
| `LREAL`                   | `double`         | -          | 64             |
| `TIME`                    |                  | -          |                |
| `LTIME`                   |                  | -          |                |
| `DATE`                    |                  | -          |                |
| `LDATE`                   |                  | -          |                |
| `TIME_OF_DAY` or `TOD`    |                  | -          |                |
| `LTIME_OF_DAY` or `LTOD`  |                  | -          |                |
| `DATE_AND_TIME` or `DT`   |                  | -          |                |
| `LDATE_AND_TIME` or `LDT` |                  | -          |                |
| `STRING`                  |                  | -          |                |
| `WSTRING`                 |                  | -          |                |
| `CHAR`                    |                  | -          |                |
| `WCHAR`                   |                  | -          |                |
| `BYTE`                    | `uint8_t`        | Unsigned   | 8              |
| `WORD`                    | `uint16_t`       | Unsigned   | 16             |
| `DWORD`                   | `uint32_t`       | Unsigned   | 32             |
| `LWORD`                   | `uint64_t`       | Unsigned   | 64             |


# 6.4.3 Generic data types

- ANY:
  - ANY_DERIVED:
  - ANY_ELEMENTARY:
    - ANY_MAGNITUDE:
      - ANY_NUM:
        - ANY_REAL:
        - ANY_INT:
          - ANY_UNSIGNED:
          - ANY_SIGNED:
      - ANY_DURATION:
    - ANY_BIT:
      - ANY_CHARS:
      - ANY_STRING:
    - ANY_CHAR:
    - ANY_DATE:


# Textual languages - common elements

- `TYPE                 ... END_TYPE`
- `VAR                  ... END_VAR`
- `VAR_INPUT            ... END_VAR`
- `VAR_OUTPUT           ... END_VAR`
- `VAR_IN_OUT           ... END_VAR`
- `VAR_EXTERNAL         ... END_VAR`
- `VAR_TEMP             ... END_VAR`
- `VAR_ACCESS           ... END_VAR`
- `VAR_GLOBAL           ... END_VAR`
- `VAR_CONFIG           ... END_VAR`

- `FUNCTION             ... END_FUNCTION`
- `FUNCTION_BLOCK       ... END_FUNCTION_BLOCK`
- `PROGRAM              ... END_PROGRAM`
- `METHOD               ... END_METHOD`
- `STEP                 ... END_STEP`
- `TRANSITION           ... END_TRANSITION`
- `ACTION               ... END_ACTION`
- `NAMESPACE            ... END_NAMESPACE`


# st operators symbols
 - nawiasy `(` `)`
 - dereference `^`
 - minus `-`
 - plus `+`
 - `NOT`
 - exponent `**`
 - multiply `*`
 - divide `/`
 - modulo `MOD`
 - comparison `>` `<` `>=` `<=`
 - equality `=`
 - inequality `<>`
 - boolean and `&` `AND`
 - boolean or `OR`
 - boolean exor `XOR`


# ST Operator Precedence

Operators of equal precedence shall be applied as written in the expression form left to right.
example: `A + B + C` is evaluated as `(A + B) + C`

when operator has two operand, the leftmost operand shall be evaluated first.
example: `SIN(A) * COS(B)` first evaluate `SIN(A)` then `COS(B)`  


 | symbols                                                                    | Precedence |
 | -------------------------------------------------------------------------- | ---------- |
 | paretheses `"(" ex ")"`                                                    | 11         |
 | function call `id "(" ex, ex, ex ")" `                                     | 10         |
 | dereference `ex "^"`                                                       | 9          |
 | unary `"-" ex`, unary `"+" ex`  `ex "NOT"`                                 | 8          |
 | exponent `ex "**" ex`                                                      | 7          |
 | `ex "*" ex` `ex "/" ex` `ex "MOD" ex`                                      | 6          |
 | `ex "+" ex` `ex "-" ex`                                                    | 5          |
 | `ex ">" ex` `ex "<" ex` `ex ">=" ex` `ex "<=" ex` `ex "=" ex` `ex "<>" ex` | 4          |
 | `ex "AND" ex` `ex "&" ex`                                                  | 3          |
 | `ex "XOR" ex`                                                              | 2          |
 | `ex "OR" ex`                                                               | 1          |


