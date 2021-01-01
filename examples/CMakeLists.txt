# Set example options.
# Optionally build the C++ examples.
option(BUILD_CPP_EXAMPLES "Build the C++ examples." ON)

if(BUILD_CPP_EXAMPLES)
    add_subdirectory(c++)
endif()
