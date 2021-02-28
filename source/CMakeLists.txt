find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(DevIL REQUIRED)
find_package(assimp REQUIRED)
find_package(glm REQUIRED)

file(GLOB ENGINE_SOURCES core/*.?pp
                         renderer/*.?pp
                         renderer/lighting/*.?pp)
file(GLOB ENGINE_INCLUDES core/*.hpp
                          renderer/*.hpp
                          lighting/*.hpp)

add_library(UrsineEngine SHARED ${ENGINE_SOURCES})
target_link_libraries(UrsineEngine PUBLIC
                      ShaderLib
                      glfw
                      ${GLEW_LIBRARIES}
                      ${IL_LIBRARIES}
                      ${ASSIMP_LIBRARIES}
                      ${GLM_LIBRARIES})

target_include_directories(UrsineEngine PUBLIC .
                           ${GLEW_INCLUDE_DIRS}
                           ${IL_INCLUDE_DIR}
                           ${ASSIMP_IMCLUDE_DIRS}
                           ${GLM_INCLUDE_DIRS})

install(TARGETS UrsineEngine LIBRARY DESTINATION ${URSINE_LIB_DIR})
install(FILES ${ENGINE_INCLUDES} DESTINATION ${URSINE_INCLUDE_DIR})
