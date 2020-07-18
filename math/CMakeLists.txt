file(GLOB MATH_SOURCES *.cpp)

add_library(UrsineMath SHARED ${MATH_SOURCES})
target_include_directories(UrsineMath PUBLIC .)

install(TARGETS UrsineMath LIBRARY DESTINATION "${URSINE_INSTALL_DIR}")
