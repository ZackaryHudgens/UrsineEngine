find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(PythonLibs 3 REQUIRED)

# CMake complains about not finding this, but it still works.
# On newer versions of CMake (>= 3.12) this is fixed.
find_package(Boost COMPONENTS python3 REQUIRED)

file(GLOB CORE_SOURCES *.cpp)

add_library(UrsineCore SHARED ${CORE_SOURCES})
target_link_libraries(UrsineCore PUBLIC
                      glfw
                      ${GLEW_LIBRARIES}
                      ${PYTHON_LIBRARIES}
                      ${Boost_LIBRARIES}
                      UrsineMath)
target_include_directories(UrsineCore PUBLIC
                           ${GLEW_INCLUDE_DIRS}
                           ${PYTHON_INCLUDE_DIR}
                           ${Boost_INCLUDE_DIRS}
                           "${PROJECT_SOURCE_DIR}/math")

add_subdirectory(python)
