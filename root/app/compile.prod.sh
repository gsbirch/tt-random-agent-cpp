#!/bin/bash

# Production Compile

# Compile the program with CMake
# This uses the CMakesLists.txt
cmake -S . -B build
cmake --build build