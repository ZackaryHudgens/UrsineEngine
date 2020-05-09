add_executable(testGame main.cpp)
target_link_libraries(testGame PUBLIC
                      UrsineMath
                      UrsineCore)
target_include_directories(testGame PUBLIC
                           "${PROJECT_SOURCE_DIR}/math"
                           "${PROJECT_SOURCE_DIR}/core")
