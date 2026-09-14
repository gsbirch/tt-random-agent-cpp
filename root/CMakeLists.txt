cmake_minimum_required(VERSION 3.20)

project(tt-random-agent-cpp)

include(FetchContent)

FetchContent_Declare(
    library
    GIT_REPOSITORY https://github.com/gsbirch/tt-client-cpp
    GIT_TAG main
)

FetchContent_MakeAvailable(library)

add_subdirectory(app)
