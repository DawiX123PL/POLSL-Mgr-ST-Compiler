cmake_minimum_required(VERSION 3.20)
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

add_definitions(-D_ITERATOR_DEBUG_LEVEL=0) 

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})



# executable file
add_executable(st_compiler ${SOURCES})

llvm_map_components_to_libnames(llvm_libs support core irreader)
target_link_libraries(st_compiler ${llvm_libs})

set_property(TARGET st_compiler PROPERTY CXX_STANDARD 17)
set_property(TARGET st_compiler PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET st_compiler PROPERTY CMAKE_CXX_EXTENSIONS Off)

target_compile_options(st_compiler PRIVATE /MD  /JMC)