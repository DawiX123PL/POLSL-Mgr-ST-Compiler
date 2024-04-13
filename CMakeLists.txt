cmake_minimum_required(VERSION 3.10)
project(st_compiler)

# source files 
set(SOURCES   
    src/console/argument_parser.cpp 
    src/console/argument_parser.hpp 
    src/console/color.cpp 
    src/console/color.hpp
    src/file/file_utils.cpp 
    src/file/file_utils.hpp
    src/lexer/st_lexer.cpp 
    src/lexer/st_lexer.hpp
    src/parser/parser.cpp 
    src/parser/parser.hpp
    src/ast/ast.hpp 
    src/ast/ast.cpp 
    src/error.hpp 
    src/main.cpp
)


# executable file
add_executable(st_compiler ${SOURCES})

set_property(TARGET st_compiler PROPERTY CXX_STANDARD 17)
set_property(TARGET st_compiler PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET st_compiler PROPERTY CMAKE_CXX_EXTENSIONS Off)

