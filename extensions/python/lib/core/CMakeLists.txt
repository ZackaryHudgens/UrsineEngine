file(GLOB PYTHON_EXT_CORE_SOURCES *.?pp
                                  wrappers/*.?pp)

add_library(core SHARED ${PYTHON_EXT_CORE_SOURCES})
target_link_libraries(core PUBLIC
                      ${PYTHON_LIBRARIES}
                      ${Boost_LIBRARIES}
                      UrsineCore
                      math)
target_include_directories(core PUBLIC .
                           ${PYTHON_INCLUDE_DIR}
                           ${Boost_INCLUDE_DIRS}
                           "${CMAKE_SOURCE_DIR}/source/core"
                           "${CMAKE_SOURCE_DIR}/extensions/python/lib/math/wrappers")

# Remove the "lib" prefix.
set_target_properties(core PROPERTIES
                      PREFIX "")

# Install as a python module.
install(TARGETS core LIBRARY DESTINATION "${URSINE_INSTALL_DIR}/python/site-packages/UrsineEngine")
