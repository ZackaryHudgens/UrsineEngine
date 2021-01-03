file(GLOB 02_SOURCES *.cpp)

add_executable(02-observers-and-notifications ${02_SOURCES})
target_link_libraries(02-observers-and-notifications PUBLIC
                      UrsineCore)
target_include_directories(02-observers-and-notifications PUBLIC
                           ${CMAKE_SOURCE_DIR}/source/core)
