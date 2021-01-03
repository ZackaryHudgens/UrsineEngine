file(GLOB 01_SOURCES *.cpp)

add_executable(01-hello-world ${01_SOURCES})
target_link_libraries(01-hello-world PUBLIC
                      UrsineCore)
target_include_directories(01-hello-world PUBLIC
                           ${CMAKE_SOURCE_DIR}/source/core)
