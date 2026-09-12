#include <iostream>
#include <string>
#include <memory>
#include "RandomAgent.h"

#ifndef RANDOM_AGENT_FACTORY
#define RANDOM_AGENT_FACTORY

class RandomAgentFactory {
    public:
        RandomAgentFactory(const std::string& url, const int port);

        std::string toString() const;
        void onStart() const;
        std::unique_ptr<RandomAgent> create() const;
        void onClose() const;
        void onStop() const;

        friend std::ostream& operator<<(std::ostream& os, const RandomAgentFactory& a);

    private:
        /** The URL of the server */
        const std::string url;

        /** The port number of the server */
        const int port;
};

#endif