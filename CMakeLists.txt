cmake_minimum_required(VERSION 3.10)
project(UrsineEngine VERSION 0.0.1
                     DESCRIPTION "A cross-platform game engine written in C++.")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set extension options.
# Optionally build the Python3 extension.
option(BUILD_PYTHON_EXTENSION "Build the Python 3 extension." ON)

set(URSINE_INSTALL_DIR "~/.local/lib")

add_subdirectory(source)
add_subdirectory(extensions)
