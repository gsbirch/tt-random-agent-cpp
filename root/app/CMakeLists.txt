add_executable(tt-random-agent
    main.cpp
    RandomAgent.cpp
    RandomAgentFactory.cpp
)

target_link_libraries(tt-random-agent
    PRIVATE
        tt
)
