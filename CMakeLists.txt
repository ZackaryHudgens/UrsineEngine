cmake_minimum_required(VERSION 3.10)
project(UrsineEngine VERSION 0.0.1
                     DESCRIPTION "A cross-platform game engine written in C++.")

# Exports compile commands as a .json file; some text editors use
# this file for syntax highlighting.
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set the install locations for libraries and header files.
set(URSINE_LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/install/lib")
set(URSINE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/install/include")

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Add subdirectories to configure.
add_subdirectory(source)

# Install the config.cmake file for find_package.
install(FILES cmake/UrsineEngineConfig.cmake DESTINATION ${URSINE_LIB_DIR}/cmake/)
