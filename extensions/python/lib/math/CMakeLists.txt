file(GLOB PYTHON_EXT_MATH_SOURCES *.?pp
                                  wrappers/*.?pp)

add_library(math SHARED ${PYTHON_EXT_MATH_SOURCES})
target_link_libraries(math PUBLIC
                      ${PYTHON_LIBRARIES}
                      ${Boost_LIBRARIES}
                      ${GLM_LIBRARIES})
target_include_directories(math PUBLIC .
                           ${PYTHON_INCLUDE_DIR}
                           ${Boost_INCLUDE_DIRS}
                           ${GLM_INCLUDE_DIRS})

# Remove the "lib" prefix.
set_target_properties(math PROPERTIES
                      PREFIX "")

# Install as a python module.
install(TARGETS math LIBRARY DESTINATION "${URSINE_INSTALL_DIR}/python/site-packages/UrsineEngine")
