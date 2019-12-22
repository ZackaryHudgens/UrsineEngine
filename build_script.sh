#!/bin/bash

# Create an install directory.
if [ ! -d install ]; then
  if [ ! -L install ]; then
    mkdir install
  fi
fi

# Run CMakeLists.txt using g++ as the compiler.
cd install
cmake -D CMAKE_CXX_COMPILER=g++ ..
make

# Copy the resources folder and move the compile_commands to the right place.
cp -r ../resources ./resources
mv compile_commands.json ../compile_commands.json

