cmake_minimum_required(VERSION 3.10)
project(st_compiler)

# source files 
set(SOURCES   
    src/argument_parser.cpp
    src/argument_parser.hpp
    src/ast.hpp
    src/console_color.cpp  
    src/console_color.hpp  
    src/error.hpp
    src/file_utils.cpp     
    src/file_utils.hpp     
    src/main.cpp
    src/st_lexer.cpp       
    src/st_lexer.hpp       
    src/st_parser.cpp      
    src/st_parser.hpp      
)


# executable file
add_executable(st_compiler ${SOURCES})

set_property(TARGET st_compiler PROPERTY CXX_STANDARD 17)
set_property(TARGET st_compiler PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET st_compiler PROPERTY CMAKE_CXX_EXTENSIONS Off)

