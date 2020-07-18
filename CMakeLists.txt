cmake_minimum_required(VERSION 3.10)
project(UrsineEngine VERSION 0.0.1
                     DESCRIPTION "A cross-platform game engine written in C++.")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(URSINE_INSTALL_DIR "~/.local/lib")

add_subdirectory(math)
add_subdirectory(core)
add_subdirectory(extensions)
