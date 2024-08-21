cmake_minimum_required(VERSION 3.20)
project(st_compiler)

#***************************************************************************************************************
# source files 

set(FRONTEND_SOURCES   
    "src/position.hpp"
    "src/frontend/main.cpp"
    "src/frontend/ast/ast1_makros.hpp"
    "src/frontend/ast/ast1.cpp"
    "src/frontend/ast/ast1.hpp"
    "src/frontend/ast/function_block.cpp"
    "src/frontend/ast/function.cpp"
    "src/frontend/ast/program.cpp"
    "src/frontend/ast/nonformal_call.cpp"
    "src/frontend/ast/formal_call.cpp"
    "src/frontend/ast/type.hpp"
    "src/frontend/lexer/st_lexer.cpp"
    "src/frontend/lexer/st_lexer.hpp"
    "src/frontend/lexer/st_token_type.cpp"
    "src/frontend/lexer/st_token_type.hpp"
    "src/frontend/parser/int_parse.hpp"
    "src/frontend/parser/st_expression_parser.cpp"
    "src/frontend/parser/st_expression_parser.hpp"
    "src/frontend/parser/st_parser.cpp"
    "src/frontend/parser/st_parser.hpp"
    "src/console/color.cpp"
    "src/console/color.hpp"
    "src/console/command_line_parser.hpp"
    "src/error/error.cpp"
    "src/error/error.hpp"
    "src/file/file_utils.cpp" 
    "src/file/file_utils.hpp"
)

set(INTERPRETER_SOURCES   
    "src/interpreter/main.cpp"
    "src/console/color.cpp"
    "src/console/color.hpp"
)

set(PACKAGER_SOURCES
    "src/packager/main.cpp"
)

set(SENDER_SOURCES
    "src/sender/data_frame/data_frame.cpp"
    "src/sender/data_frame/data_frame.hpp"
    "src/sender/main.cpp"
)



#***************************************************************************************************************
# executable file
add_executable(st_compiler ${FRONTEND_SOURCES})
add_executable(interpreter ${INTERPRETER_SOURCES})
add_executable(packager ${PACKAGER_SOURCES})
add_executable(sender ${SENDER_SOURCES})

target_include_directories(st_compiler PUBLIC "src")
target_include_directories(interpreter PUBLIC "src")
target_include_directories(packager PUBLIC "src")
target_include_directories(sender PUBLIC "src")

#***************************************************************************************************************
# include llvm headers
# and link llvm binaries

add_definitions(-D_ITERATOR_DEBUG_LEVEL=2) 

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

llvm_map_components_to_libnames(
# libraries object
    st_compiler_llvm_libraries  

# required libraries
    support 
    core  
    irreader
        
    armasmparser
    armcodegen
    armdesc
    armdisassembler
    arminfo
    armutils

    x86asmparser
    x86codegen
    x86desc
    x86disassembler
    x86info
)

llvm_map_components_to_libnames(
# libraries object
    interpreter_llvm_libraries  
    
# required libraries
    x86asmparser
    x86codegen
    x86desc
    x86disassembler
    x86info

    MCJIT 
    executionengine
    interpreter
)


target_link_libraries(st_compiler ${st_compiler_llvm_libraries})
target_link_libraries(interpreter ${interpreter_llvm_libraries})

set_property(TARGET st_compiler PROPERTY CXX_STANDARD 17)
set_property(TARGET st_compiler PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET st_compiler PROPERTY CMAKE_CXX_EXTENSIONS Off)

set_property(TARGET interpreter PROPERTY CXX_STANDARD 17)
set_property(TARGET interpreter PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET interpreter PROPERTY CMAKE_CXX_EXTENSIONS Off)

set_property(TARGET packager PROPERTY CXX_STANDARD 17)
set_property(TARGET packager PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET packager PROPERTY CMAKE_CXX_EXTENSIONS Off)

set_property(TARGET sender PROPERTY CXX_STANDARD 17)
set_property(TARGET sender PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET sender PROPERTY CMAKE_CXX_EXTENSIONS Off)

if ( MSVC )
    target_compile_options(st_compiler PRIVATE /MDd  /JMC)
    target_compile_options(interpreter PRIVATE /MDd  /JMC)
    target_compile_options(packager PRIVATE /MDd  /JMC)
    target_compile_options(sender PRIVATE /MDd  /JMC)
endif ( MSVC )

#***************************************************************************************************************
# add Boost includes and binaries

set(Boost_USE_STATIC_LIBS OFF) 
set(Boost_USE_MULTITHREADED ON)  
set(Boost_USE_STATIC_RUNTIME OFF) 

set(BOOST_ROOT "C:/boost")
find_package(Boost)

if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    target_compile_options(st_compiler PUBLIC -DBOOST_ALL_NO_LIB)
    target_compile_options(interpreter PUBLIC -DBOOST_ALL_NO_LIB)
    target_compile_options(packager PUBLIC -DBOOST_ALL_NO_LIB)
    target_compile_options(sender PUBLIC -DBOOST_ALL_NO_LIB)
else()
    message(FATAL_ERROR "Could not find Boost libraries")
endif()


#***************************************************************************************************************
# Copy GCC object files to build directory
file(COPY "${PROJECT_SOURCE_DIR}/arm-none-eabi-gcc_libs/lib" DESTINATION "${CMAKE_BINARY_DIR}/build")

#***************************************************************************************************************
# produce stl files

find_package(Python3 REQUIRED)
message("Generating STL types conversion functions")

file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/build/stl/")

execute_process(
    COMMAND ${Python3_EXECUTABLE} ./stl/conversion_func_producer.py --st_file "${CMAKE_BINARY_DIR}/build/stl/conv.st_extern" --c_file "${CMAKE_BINARY_DIR}/build/stl/conv.c"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    RESULT_VARIABLE CONVERSION_FUNC_PRODUCER_RESULT
)

if(CONVERSION_FUNC_PRODUCER_RESULT)
    message(FATAL_ERROR "Generating STL types failed with result: ${CONVERSION_FUNC_PRODUCER_RESULT}")
endif()


#***************************************************************************************************************
# change default out dir
set_target_properties( st_compiler interpreter packager sender
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/bin"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/bin"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/bin"
)


# target_compile_options(st_compiler PUBLIC "-Wunused-result" "-Wall")


# trick from https://stackoverflow.com/questions/7747857/in-cmake-how-do-i-work-around-the-debug-and-release-directories-visual-studio-2
# prevents creating Debug and Release directories
if ( MSVC )


	set_target_properties( st_compiler interpreter packager sender
		PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY           "${CMAKE_BINARY_DIR}/build/bin"
		ARCHIVE_OUTPUT_DIRECTORY_DEBUG     "${CMAKE_BINARY_DIR}/build/bin"
		ARCHIVE_OUTPUT_DIRECTORY_RELEASE   "${CMAKE_BINARY_DIR}/build/bin"
		LIBRARY_OUTPUT_DIRECTORY           "${CMAKE_BINARY_DIR}/build/bin"
		LIBRARY_OUTPUT_DIRECTORY_DEBUG     "${CMAKE_BINARY_DIR}/build/bin"
		LIBRARY_OUTPUT_DIRECTORY_RELEASE   "${CMAKE_BINARY_DIR}/build/bin"
		RUNTIME_OUTPUT_DIRECTORY           "${CMAKE_BINARY_DIR}/build/bin"
		RUNTIME_OUTPUT_DIRECTORY_DEBUG     "${CMAKE_BINARY_DIR}/build/bin"
		RUNTIME_OUTPUT_DIRECTORY_RELEASE   "${CMAKE_BINARY_DIR}/build/bin"
	)

endif ( MSVC )

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

#***************************************************************************************************************
# surpress compiler warnings C4624 - "destructor was implicitly defined as deleted"
# surpress compiler warning LNK4099 - "PDB '' was not found with ..."

if ( MSVC )
    target_compile_options(st_compiler PRIVATE /wd4624)
    target_compile_options(interpreter PRIVATE /wd4624)
    set_target_properties(st_compiler PROPERTIES LINK_FLAGS "/ignore:4099")
    set_target_properties(interpreter PROPERTIES LINK_FLAGS "/ignore:4099")
endif ( MSVC )

