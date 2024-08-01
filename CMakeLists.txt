cmake_minimum_required(VERSION 3.20)
project(st_compiler)

#***************************************************************************************************************
# source files 

set(SOURCES   
    "src/console/command_line_parser.hpp"
    "src/console/color.cpp"
    "src/console/color.hpp"
    "src/file/file_utils.cpp"
    "src/file/file_utils.hpp"

    "src/lexer/st_lexer.cpp"
    "src/lexer/st_lexer.hpp"
    "src/lexer/st_token_type.cpp"
    "src/lexer/st_token_type.hpp"

    "src/parser/st_expression_parser.cpp "
    "src/parser/st_expression_parser.hpp"

    "src/parser/st_parser.cpp"
    "src/parser/st_parser.hpp"

    "src/ast/ast1.hpp"
    "src/ast/ast1.cpp"

    "src/ast/function_block.cpp"
    "src/ast/function.cpp"
    "src/ast/program.cpp"

    "src/error.cpp"
    "src/error.hpp"
    "src/main.cpp"
)

#***************************************************************************************************************
# executable file
add_executable(st_compiler ${SOURCES})
add_executable(interpreter 
"src/interpreter/main.cpp"
"src/console/color.cpp"
"src/console/color.hpp"
)

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
    llvm_libs  
    mc   
    support 
    core  
    irreader
    
    
    aarch64asmparser
    aarch64codegen
    aarch64desc
    aarch64disassembler
    aarch64info
    aarch64utils
    
    amdgpuasmparser
    amdgpucodegen
    amdgpudesc
    amdgpudisassembler
    amdgpuinfo
    amdgputargetmca
    amdgpuutils
    
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
    # x86utils
    # engine 
    executionengine
    interpreter

    MCJIT 
    ExecutionEngine 
    Target 
    Analysis 
    ProfileData 
    Symbolize 
    DebugInfoBTF 
    DebugInfoPDB 
    DebugInfoMSF 
    DebugInfoDWARF 
    RuntimeDyld 
    OrcTargetProcess 
    OrcShared 
    Object 
    TextAPI 
    MCParser 
    IRReader 
    AsmParser 
    BitReader 
    MC 
    DebugInfoCodeView 
    Core 
    Remarks 
    BitstreamReader 
    BinaryFormat 
    TargetParser 
    Support 
    Demangle
)


target_link_libraries(st_compiler ${llvm_libs})
target_link_libraries(interpreter ${llvm_libs})

set_property(TARGET st_compiler PROPERTY CXX_STANDARD 17)
set_property(TARGET st_compiler PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET st_compiler PROPERTY CMAKE_CXX_EXTENSIONS Off)

set_property(TARGET interpreter PROPERTY CXX_STANDARD 17)
set_property(TARGET interpreter PROPERTY CXX_STANDARD_REQUIRED ON)
set_property(TARGET interpreter PROPERTY CMAKE_CXX_EXTENSIONS Off)

if ( MSVC )
    target_compile_options(st_compiler PRIVATE /MDd  /JMC)
    target_compile_options(interpreter PRIVATE /MDd  /JMC)
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
else()
    message(FATAL_ERROR "Could not find Boost libraries")
endif()

#***************************************************************************************************************
# change default out dir
set_target_properties( st_compiler interpreter
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build/"
)

# target_compile_options(st_compiler PUBLIC "-Wunused-result" "-Wall")


# trick from https://stackoverflow.com/questions/7747857/in-cmake-how-do-i-work-around-the-debug-and-release-directories-visual-studio-2
# prevents creating Debug and Release directories
if ( MSVC )


	set_target_properties( st_compiler interpreter
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

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

