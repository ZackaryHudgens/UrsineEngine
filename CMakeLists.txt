cmake_minimum_required(VERSION 3.10)
project(UrsineEngine VERSION 0.0.1
                     DESCRIPTION "A cross-platform game engine written in C++.")

# Exports compile commands as a .json file; some text editors use
# this file for syntax highlighting.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Sets the install location for the UrsineEngine (and any extensions).
set(URSINE_INSTALL_DIR "~/.local/lib")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Include the resource compiler.
include("CMakeRC.cmake")

add_subdirectory(source)
add_subdirectory(extensions)
