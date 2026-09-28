include(FetchContent)
FetchContent_Declare(
    cxxopts
    GIT_REPOSITORY https://github.com/jarro2783/cxxopts.git
    GIT_TAG v3.2.0
)
FetchContent_MakeAvailable(cxxopts)

add_executable(tt-random-agent
    main.cpp
    RandomAgent.cpp
    RandomAgentFactory.cpp
)

find_package(OpenSSL REQUIRED)

target_link_libraries(tt-random-agent
    PRIVATE
        tt
        OpenSSL::SSL
        OpenSSL::Crypto
        cxxopts::cxxopts
)
