find_package(PythonLibs 3 REQUIRED)

# CMake complains about not finding this, but it still works.
# On newer versions of CMake (>= 3.12) this is fixed.
find_package(Boost COMPONENTS python3 REQUIRED)

add_subdirectory(core)

# Add __init__.py so the module is recognized.
file(WRITE "__init__.py" "${URSINE_INSTALL_DIR}/python3.6/site-packages/UrsineEngine")
