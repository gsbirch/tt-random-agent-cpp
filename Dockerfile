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
WORKDIR /app

#-------------------------------------------------------------------------------
# Development Phase
# The instructions in this section only run if you build the image with
# `--target dev`. Put instructions here that should only run when you are
# testing and developing the image. This section assumes there is a container
# named `tt-web` running as a test version of the Tandem Tales web server.
#-------------------------------------------------------------------------------
FROM base AS dev

# Allow running the sh files
RUN chmod +x /app/compile.dev.sh
RUN chmod +x /app/run.dev.sh

# Build the agent
RUN ./compile.dev.sh

# Clean up the container
RUN apt purge -y git
RUN apt autoremove -y
RUN apt clean
RUN rm -rf /var/lib/apt/lists/*

# Run the development version of the entrypoint script and keep the shell open.
CMD ["sh", "-c", "trap 'exec bash' INT; /app/run.dev.sh; exec bash"]

#-------------------------------------------------------------------------------
# Production Phase
# The instructions in this section run if you build the image with
# `--target prod`. Since this is the last phase defined, these instructions will
# run by default if you don't specify a target. Put instructions here that
# should only run in the final, working version of your image.
#-------------------------------------------------------------------------------
FROM base AS prod

# Allow running the sh files
RUN chmod +x /app/compile.prod.sh
RUN chmod +x /app/run.prod.sh

# Build the agent
RUN ./compile.prod.sh

# Clean up the container
RUN apt purge -y git
RUN apt autoremove -y
RUN apt clean
RUN rm -rf /var/lib/apt/lists/*

# Run the production version of the entrypoint script.
CMD ["sh", "-c", "/app/run.prod.sh"]