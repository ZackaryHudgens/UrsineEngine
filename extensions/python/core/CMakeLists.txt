file(GLOB CORE_PYTHON_SOURCES *.cpp)

add_library(core SHARED ${CORE_PYTHON_SOURCES})
target_link_libraries(core PUBLIC
                      ${PYTHON_LIBRARIES}
                      ${Boost_LIBRARIES}
                      UrsineCore)
target_include_directories(core PUBLIC .
                           ${PYTHON_INCLUDE_DIR}
                           ${Boost_INCLUDE_DIRS}
                           "${PROJECT_SOURCE_DIR}/core")

# Remove the "lib" prefix.
set_target_properties(core PROPERTIES
                      PREFIX "")

# Install as a python module.
install(TARGETS core LIBRARY DESTINATION "${URSINE_INSTALL_DIR}/python3.6/site-packages/UrsineEngine")
