file(GLOB 03_SOURCES *.cpp)

add_executable(03-signals ${03_SOURCES})
target_link_libraries(03-signals PUBLIC
                      UrsineCore)
target_include_directories(03-signals PUBLIC
                           ${CMAKE_SOURCE_DIR}/source/core)
