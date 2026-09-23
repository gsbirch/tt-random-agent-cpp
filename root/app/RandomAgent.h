#include <string>
#include <ostream>
#include <tt/Client.h>


#ifndef RANDOM_AGENT_H
#define RANDOM_AGENT_H

class RandomAgent : public tt::Client {
    /*
    A Tandem Tales agent that makes random choices according to this policy:
    
    - If this is a normal turn, the agent chooses to `PASS` control to its
    partner 30% of the time. If not passing, it chooses a non-`PASS` action
    uniformly at random.
    - If this is a `SUCCEED`/`FAIL` decision, the agent chooses `SUCCEED` 80% of
    the time.
    
    Arguments:
        url (str): The URL of the Tandem Tales server.
        port (int): The network port of the Tandem Tales server.
    */

    public:
        /** The default server URL used if none is provided */
        static const std::string DEFAULT_URL;

        /** The default network port used if none is provided */
        static const int DEFAULT_PORT;

        /** A unique ID number used to identify this agent */
        int id = nextID++;

        /** Max milliseconds this agent will wait before taking a turn */
        const long delay;


        RandomAgent(const std::string& url = "", const int port = 0);

        std::string toString() const;
        void onConnect(std::string connect);
        void onStart(std::string world, std::string role, std::string state);
        void onUpdate(std::string status);
        int onChoice(std::string status);
        void onEnd(std::string ending);
        void onClose();
        void onStop(std::string message);
        void onDisconnect(std::string);

        friend std::ostream& operator<<(std::ostream& os, const RandomAgent& a);

    private:
        // this agent's ID
        // int id;

        // ID number that will be assigned to the next agent created.
        static int nextID;

        /** Probability that this agent will pass control to its partner */
        static const double PASS_PROBABILITY;

        /** Probability that this agent will agree to a proposed joint action */
        static const double SUCCEED_PROBABILITY;

        /** The default delay if none is provided */
        static const long DEFAULT_DELAY;

        /** The ID number of the next agent to be created */
        // static int nextID;

        /** The random number generator used to make decisions */
        // static final Random random;
};

#endif