cmake_minimum_required(VERSION 3.10)
project(UrsineEngine VERSION 0.0.1
                     DESCRIPTION "A cross-platform game engine written in C++.")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(URSINE_INSTALL_DIR "~/.local/lib")

add_subdirectory(core)

# Optionally build the Python3 extension.
option(BUILD_PYTHON "Build the Python 3 extension." ON)

if(BUILD_PYTHON)
  add_subdirectory(python)
endif()
