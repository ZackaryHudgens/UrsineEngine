add_library(core SHARED Core.cpp)
target_link_libraries(core PUBLIC
                      ${PYTHON_LIBRARIES}
                      ${Boost_LIBRARIES}
                      UrsineCore)
target_include_directories(core PUBLIC
                           ${PYTHON_INCLUDE_DIR}
                           ${Boost_INCLUDE_DIRS}
                           "${PROJECT_SOURCE_DIR}/core")

# Remove the "lib" prefix.
set_target_properties(core PROPERTIES
                      PREFIX "")
