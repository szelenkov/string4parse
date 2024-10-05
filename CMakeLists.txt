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

project ("string4parse" VERSION 3.0.0 LANGUAGES CXX)

# Add source to this project's executable.
add_executable (string4parse "src/string4parse.cpp" "include/string4parse.h")

set_property(TARGET string4parse PROPERTY CXX_STANDARD 20)

# TODO: Add tests and install targets if needed.
