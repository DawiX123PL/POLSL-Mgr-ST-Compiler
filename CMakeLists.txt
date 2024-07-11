cmake_minimum_required(VERSION 3.20)
project(st_compiler)

# source files 
set(SOURCES   
    src/console/command_line_parser.hpp
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

if ( MSVC )
    target_compile_options(st_compiler PRIVATE /MD  /JMC)
endif ( MSVC )


# change default out dir
set_target_properties( st_compiler
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/"
)

# trick from https://stackoverflow.com/questions/7747857/in-cmake-how-do-i-work-around-the-debug-and-release-directories-visual-studio-2
# prevents creating Debug and Release directories
if ( MSVC )


	set_target_properties( st_compiler
		PROPERTIES
		ARCHIVE_OUTPUT_DIRECTORY           "${CMAKE_BINARY_DIR}/build/"
		ARCHIVE_OUTPUT_DIRECTORY_DEBUG     "${CMAKE_BINARY_DIR}/build/"
		ARCHIVE_OUTPUT_DIRECTORY_RELEASE   "${CMAKE_BINARY_DIR}/build/"
		LIBRARY_OUTPUT_DIRECTORY           "${CMAKE_BINARY_DIR}/build/"
		LIBRARY_OUTPUT_DIRECTORY_DEBUG     "${CMAKE_BINARY_DIR}/build/"
		LIBRARY_OUTPUT_DIRECTORY_RELEASE   "${CMAKE_BINARY_DIR}/build/"
		RUNTIME_OUTPUT_DIRECTORY           "${CMAKE_BINARY_DIR}/build/"
		RUNTIME_OUTPUT_DIRECTORY_DEBUG     "${CMAKE_BINARY_DIR}/build/"
		RUNTIME_OUTPUT_DIRECTORY_RELEASE   "${CMAKE_BINARY_DIR}/build/"
	)

endif ( MSVC )

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "") # works

