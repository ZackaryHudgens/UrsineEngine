#!/bin/bash

# Create an install directory.
if [ ! -d build ]; then
  if [ ! -L build ]; then
    mkdir build
  fi
fi

# Run CMakeLists.txt using g++ as the compiler.
cd build
cmake -D CMAKE_CXX_COMPILER=g++ ..
make install

# Move the compile_commands to the right place.
mv compile_commands.json ../compile_commands.json
