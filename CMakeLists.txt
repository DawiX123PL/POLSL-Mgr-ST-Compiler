cmake_minimum_required(VERSION 3.10)
project(st_compiler)

# source files 
set(SOURCES
    src/argument_parser.cpp
    src/argument_parser.hpp
    src/console_color.cpp  
    src/console_color.hpp  
    src/error.hpp
    src/file_utils.cpp     
    src/file_utils.hpp     
    src/main.cpp
    src/st_lexer.cpp       
    src/st_lexer.hpp       
)


# executable file
add_executable(st_compiler ${SOURCES})


