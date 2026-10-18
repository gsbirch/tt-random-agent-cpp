#===============================================================================
# Tandem Tales Agent (C++) Docker Image
# 
# This Dockerfile defines a container (a lightweight virtual machine) that
# includes an operating system, g++ and CMake for compiling, the Tandem Tales C++
# Client library, and the source code for a Tandem Tales agent, along with some
# necessary packages for networking.
#===============================================================================

# Start with Linux
FROM ubuntu:24.04 AS base

# Update packages.
RUN apt update
# Git downloads the Tandem Tales C++ library.
# g++ and cmake compile the C++ project
RUN apt install -y git g++ cmake
# These are used to open an ssl connection to the server
# and to make external API calls
RUN apt install -y openssl libssl-dev libcurl4-openssl-dev ca-certificates

# Copy the agent's files into the image.
COPY ./root /

# Set `/app` as the working directory.
WORKDIR /

# Compile the C++ agent
RUN cmake -S . -B build
RUN cmake --build build

# Clean up the container
RUN apt purge -y git
RUN apt autoremove -y
RUN apt clean
RUN rm -rf /var/lib/apt/lists/*

# Run the agent
CMD ["./build/app/tt-random-agent"]