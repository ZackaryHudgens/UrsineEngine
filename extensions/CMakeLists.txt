# Set extension options.
# Optionally build the Python3 extension.
option(BUILD_PYTHON_EXTENSION "Build the Python 3 extension." ON)

if(BUILD_PYTHON_EXTENSION)
  add_subdirectory(python)
endif()
