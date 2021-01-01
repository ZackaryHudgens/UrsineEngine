# Set extension options.
# Optionally build the Python3 extension.
option(BUILD_PYTHON_EXTENSION "Build the Python 3 extension." OFF)

if(BUILD_PYTHON_EXTENSION)
  add_subdirectory(python)
endif()
