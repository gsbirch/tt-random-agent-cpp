#!/bin/bash

# Development Compile

# This includes extra flags for debug information and AddressSanitizer

EXTRA=""
if [ -d /library ]; then
  EXTRA="-DFETCHCONTENT_SOURCE_DIR_LIBRARY=/library"
fi

# Compile the program with CMake
# This uses the CMakesLists.txt
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug \
  -DCMAKE_CXX_FLAGS="-g -O0 -fsanitize=address,undefined -fno-omit-frame-pointer" \
  $EXTRA
cmake --build build