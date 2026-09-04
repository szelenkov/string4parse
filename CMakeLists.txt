# CMakeList.txt : CMake project for string4parse, include source and define
# project specific logic here.

# We require a CMake version greater than or equal to 3.24 on Windows in order to
# support specifying target_include_directories with SYSTEM for Visual Studio Generators
# see: https://cmake.org/cmake/help/latest/release/3.24.html#generators
cmake_minimum_required(VERSION 3.24)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("string4parse" LANGUAGES CXX)

# require C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# example library
add_library(string4parse_lib "src/string4parse.cpp" "include/string4parse.h")

set_property(TARGET string4parse_lib PROPERTY CXX_STANDARD 20)

# testing binary
add_executable(string4parse_test "tests/string4parse_test.cpp")
target_link_libraries(string4parse_test PRIVATE string4parse_lib)
# enable testing functionality
enable_testing()

include(ExternalProject)
# Download and install GoogleTest
ExternalProject_Add(
    gtest
    URL https://github.com/google/googletest/archive/release-1.12.1.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/gtest
    # Disable install step
    INSTALL_COMMAND ""
)

# Get GTest source and binary directories from CMake project
ExternalProject_Get_Property(gtest source_dir binary_dir)

# Create a libgtest target to be used as a dependency by test programs
add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

# define tests
add_test(NAME string4parse_test COMMAND $<TARGET_FILE:string4parse_test>)