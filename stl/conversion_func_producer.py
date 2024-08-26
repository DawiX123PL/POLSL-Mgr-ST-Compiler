import argparse

cli_parser = argparse.ArgumentParser(
    prog='conversion_func_producer.py',
    description='This program produces conversion functions used in ST programming language',
    epilog='')

cli_parser.add_argument('--st_file', required=True)
cli_parser.add_argument('--c_file', required=True)
cli_parser.add_argument('--version', action="version")

cli = cli_parser.parse_args()

data_types = [
    ("BOOL", "bool"),
    ("SINT", "int8_t"),
    ("INT", "int16_t"),
    ("DINT", "int32_t"),
    ("LINT", "int64_t"),
    ("USINT", "uint8_t"),
    ("UINT", "uint16_t"),
    ("UDINT", "uint32_t"),
    ("ULINT", "uint64_t"),
    ("REAL", "float"),
    ("LREAL", "double"),
    ("BYTE", "uint8_t"),
    ("WORD", "uint16_t"),
    ("DWORD", "uint32_t"),
    ("LWORD", "uint64_t"),
]


def ProduceSTFunctionExtern(source_type, dest_type):
    st_body = \
        f"""
FUNCTION {source_type}_TO_{dest_type} : {dest_type}
    VAR_INPUT
        input: {source_type};
    END_VAR
    ;
    // this function is declared as extern
    // body should be defined elsewhere
END_FUNCTION
"""
    return st_body


def ProduceCFunction(source_type, dest_type):
    st_body = \
        f"""
{dest_type} {source_type}_TO_{dest_type}(void* global_memory_pointer, {source_type} input)
{{
    return input;
}}
"""
    return st_body


def ProduceCtypedef(c_type, st_type):
    return f"typedef {c_type} {st_type};"


st_file_content = ""

for source_type in data_types:
    for dest_type in data_types:
        st_file_content += ProduceSTFunctionExtern(
            source_type[0], dest_type[0])
        st_file_content += "\n"

c_file_content = """

#include <stdint.h>
#include <stdbool.h>

"""

for data_type in data_types:
    st_type = data_type[0]
    c_type = data_type[1]
    c_file_content += ProduceCtypedef(c_type, st_type)
    c_file_content += "\n"


for source_type in data_types:
    for dest_type in data_types:
        c_file_content += ProduceCFunction(source_type[0], dest_type[0])
        c_file_content += "\n"


if cli.st_file is not None:
    with open(cli.st_file, 'w') as f:
        f.write(st_file_content)


if cli.c_file is not None:
    with open(cli.c_file, 'w') as f:
        f.write(c_file_content)

