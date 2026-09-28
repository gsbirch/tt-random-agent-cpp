#pragma once

#include "RandomAgent.h"

#include <iostream>
#include <string>
#include <memory>

#include <tt/ClientFactory.h>

#ifndef RANDOM_AGENT_FACTORY
#define RANDOM_AGENT_FACTORY

/**
 * A factory that continuously creates {@link RandomAgent}s as needed.
 */
class RandomAgentFactory: public tt::ClientFactory {
    public:
        /**
         * Creates a new random agent factory that connects to a Tandem Tales server
         * on the given URL and port number.
         * 
         * @param url the URL of the server
         * @param port the port number of the server
         */
        RandomAgentFactory(const std::string& url, const int port);

        std::string toString() const override;
        void onStart() const override;
        std::unique_ptr<tt::Client> create() const override;
        void onClose() const override;
        void onStop() const override;

    private:
        /** The URL of the server */
        const std::string url;

        /** The port number of the server */
        const int port;
};

#endif