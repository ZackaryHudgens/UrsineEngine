find_package(Catch2 REQUIRED)

file(GLOB MATH_TEST_SOURCES *.cpp)

add_executable(UrsineMathTests ${MATH_TEST_SOURCES})
target_include_directories(UrsineMathTests PUBLIC
                           "${PROJECT_SOURCE_DIR}/math")
target_link_libraries(UrsineMathTests PUBLIC
                      UrsineMath
                      Catch2::Catch2)
