#add_subdirectory(util)

find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

file(GLOB CORE_SOURCES *.cpp)

add_library(UrsineCore SHARED ${CORE_SOURCES})
target_link_libraries(UrsineCore PUBLIC
                      glfw
                      ${GLEW_LIBRARIES}
                      #UrsineUtil
                      UrsineMath)
target_include_directories(UrsineCore PUBLIC
                           ${GLEW_INCLUDE_DIRS}
                           "${PROJECT_SOURCE_DIR}/math"
                           "${PROJECT_SOURCE_DIR}/core/util")
