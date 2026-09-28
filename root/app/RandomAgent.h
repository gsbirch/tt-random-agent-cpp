#pragma once

#include <string>
#include <ostream>

#include <tt/Client.h>
#include <tt/io/Connect.h>

#ifndef RANDOM_AGENT_H
#define RANDOM_AGENT_H

/**
 * A Tandem Tales agent that makes random choices. This agent can play as either
 * role, in any story world, and with any partner.
 * <p>
 * This agent follows a simple process when making its choices. When choosing a
 * turn, the agent has a {@link #PASS_PROBABILITY} chance to pass control to its
 * partner. If it does not pass, it chooses a non-pass action uniformly at
 * random. There is one exception to this rule. When this agent has to decide on
 * a join action proposed by its partner, it has a {@link SUCCEED_PROBABILITY}
 * chance of letting the action succeed.
 * <p>
 * This agent waits a random number of milliseconds up to {@link #delay} to give
 * the impression that it is thinking. If the delay is set to 0, the agent will
 * take turns with no delay.
 */

class RandomAgent : public tt::Client {
    public:
        /** The default server URL used if none is provided */
        static const std::string DEFAULT_URL;

        /** The default network port used if none is provided */
        static const int DEFAULT_PORT;

        /** A unique ID number used to identify this agent */
        int id = nextID++;

        /** Max milliseconds this agent will wait before taking a turn */
        const long delay;

        /**
         * Creates a new random agent with the given settings.
         * 
         * @param url the URL of the server to connect to
         * @param port the network port to connect to the server on
         * @param seed the seed used by the pseudo-random number generator that
         * make decisions
         * @param delay the max milliseconds to wait before taking a turn
         */
        RandomAgent(const std::string& url, int port, long seed, long delay);

        /**
         * Creates a new random agent with the given settings.
         * 
         * @param url the URL of the server to connect to
         * @param port the network port to connect to the server on
         * @param delay the max milliseconds to wait before taking a turn
         */
        RandomAgent(const std::string& url, int port, long delay);

        /**
         * Creates a new random agent with a random starting seed and the {@link
         * #DEFAULT_DELAY default delay} time.
         * 
         * @param url the URL of the server to connect to
         * @param port the network port to connect to the server on
         */
        RandomAgent(const std::string& url, int port);

        /**
         * Creates a new random agent with a random starting seed and default
         * settings.
         */
        RandomAgent();

        std::string toString() const override;
        void onConnect(const tt::Connect* connect) override;
        void onStart(const tt::World* world, tt::Role role, const tt::State* state) override;
        void onUpdate(const tt::Status* status) override;
        int onChoice(const tt::Status* status) override;
        void onEnd(const tt::Ending *ending) override;
        void onStop(std::string message) override;
        void onClose() override;
        void onDisconnect() override;

        // friend std::ostream& operator<<(std::ostream& os, const RandomAgent& a);

    private:
        /** Probability that this agent will pass control to its partner */
        static const double PASS_PROBABILITY;

        /** Probability that this agent will agree to a proposed joint action */
        static const double SUCCEED_PROBABILITY;

        /** The default delay if none is provided */
        static const long DEFAULT_DELAY;

        /** The ID number of the next agent to be created */
        static int nextID;

        /**
         * Checks whether this agent has been asked to agree (succeed) or disagree
         * (fail) a proposed joint action.
         * 
         * @param status the current status passed to this agent by the server
         * @return true if the agent is currently responding to a proposal, or false
         * if this is a normal turn
         */
        static bool isProposal(const tt::Status* status);
};

#endif