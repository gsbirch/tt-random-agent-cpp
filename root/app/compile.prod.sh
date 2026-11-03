#!/bin/bash

# Production Compile

# Compile the program with CMake
# This uses the CMakesList.txt
cmake -S . -B build
cmake --build build