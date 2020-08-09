file(GLOB MATH_PYTHON_SOURCES *.cpp)

add_library(math SHARED ${MATH_PYTHON_SOURCES})
target_link_libraries(math PUBLIC
                      ${PYTHON_LIBRARIES}
                      ${Boost_LIBRARIES}
                      UrsineMath)
target_include_directories(math PUBLIC .
                           ${PYTHON_INCLUDE_DIR}
                           ${Boost_INCLUDE_DIRS}
                           "${PROJECT_SOURCE_DIR}/math")

# Remove the "lib" prefix.
set_target_properties(math PROPERTIES
                      PREFIX "")

# Install as a python module.
install(TARGETS math LIBRARY DESTINATION "${URSINE_INSTALL_DIR}/python3.6/site-packages/UrsineEngine")
