file(GLOB 02_SOURCES *.cpp)

add_executable(02-gameobjects-and-components ${02_SOURCES})
target_link_libraries(02-gameobjects-and-components PUBLIC
                      UrsineCore)
target_include_directories(02-gameobjects-and-components PUBLIC
                           ${CMAKE_SOURCE_DIR}/source/core)
