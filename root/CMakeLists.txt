cmake_minimum_required(VERSION 3.20)

project(tt-client
    LANGUAGES CXX
)

add_executable(my_app
    app/main.cpp
    # app/foo.cpp
    # app/bar.cpp
)

target_compile_features(my_app PRIVATE cxx_std_17)
