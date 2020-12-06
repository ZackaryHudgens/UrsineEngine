find_package(PythonLibs 3 REQUIRED)

# CMake complains about not finding this, but it still works.
# On newer versions of CMake (>= 3.12) this is fixed.
find_package(Boost COMPONENTS python REQUIRED)

message(STATUS "PYTHON_LIBRARIES = ${PYTHON_LIBRARIES}")
message(STATUS "PYTHON_INCLUDE_DIRS = ${PYTHON_INCLUDE_DIRS}")
message(STATUS "Boost_LIBRARIES = ${Boost_LIBRARIES}")

add_subdirectory(lib)
