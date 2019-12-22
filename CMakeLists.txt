cmake_minimum_required(VERSION 3.10.2)
project(a_game)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL2 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(DevIL REQUIRED)
include_directories("src" ${SDL2_INCLUDE_DIRS})

file(GLOB SOURCES "src/*.cpp")

add_executable(a_game ${SOURCES})
target_link_libraries(a_game ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} ${IL_LIBRARIES} ${ILU_LIBRARIES})
