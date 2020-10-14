find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(DevIL REQUIRED)
find_package(assimp REQUIRED)
find_package(glm REQUIRED)

file(GLOB CORE_SOURCES *.?pp)

add_library(UrsineCore SHARED ${CORE_SOURCES})
target_link_libraries(UrsineCore PUBLIC
                      glfw
                      ${GLEW_LIBRARIES}
                      ${IL_LIBRARIES}
                      ${ASSIMP_LIBRARIES}
                      ${GLM_LIBRARIES})

target_include_directories(UrsineCore PUBLIC
                           ${GLEW_INCLUDE_DIRS}
                           ${IL_INCLUDE_DIR}
                           ${ASSIMP_IMCLUDE_DIRS}
                           ${GLM_INCLUDE_DIRS})

install(TARGETS UrsineCore LIBRARY DESTINATION "${URSINE_INSTALL_DIR}")
