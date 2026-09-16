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
)
