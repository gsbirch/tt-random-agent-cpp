/*
This is an example of a Tandem Tales agent and agent factory in Python. The
agent makes random decisions. The factory continuously creates new agents as
they are needed by the server. Both the agent and factory print messages
during important moments in their lifecycle to demonstrate how to use those
methods.
*/

/*
import random
import time
import tt
*/

#include "RandomAgent.h"
#include <string>
#include <iostream>
#include <tt/Role.h>

const double RandomAgent::PASS_PROBABILITY = 0.3;
const double RandomAgent::SUCCEED_PROBABILITY = 0.8;
const long RandomAgent::DEFAULT_DELAY = 5000;
int RandomAgent::nextID = 0;

const std::string RandomAgent::DEFAULT_URL = "localhost";
const int RandomAgent::DEFAULT_PORT = 9005;
//Client.DEFAULT_PORT;

RandomAgent::RandomAgent(const std::string& url, const int port):
    Client("random", "", "", tt::Role::NONE, "", "", url, port), delay(DEFAULT_DELAY) {
    /*
    The arguments to `tt.Client` are:
    1. name: This agent's name. Hard-code this. Use up to 20 letters,
       digits, and undersocres.
    2. password: This should be left None so the Client will read it from
       the environment variables. Do not hard-code the password.
    3. world: The name of the world the agent wants to play in. Leave this
       None to play any world. Hard-code this if the agent is only
       designed to play in one story world.
    4. role: The role this client will have, which is either tt.PLAYER or
       tt.GM (for game master), or None for either role. Hard-code this if
       the agent is only designed to play as one role.
    5. partner: The partner this agents wants to play with. Leave this
       None to play with any partner. Hard-code this if the agent is only
       designed to play with one type of partner.
    6. key: The API key used for the external API. This should be left
       None so the Client will read it from the environment variables.
    7. url: The URL of the Tandem Tales server.
    8. port: The network port of the Tandem Tales server.
    */
}

std::string RandomAgent::toString() const
{
    return "Random Agent " + std::to_string(id);
}

// Optional: Runs when the client connects to the server.
void RandomAgent::onConnect(std::string connect)
{
    std::cout << *this << " has connected to the server." << std::endl;
}

// Optional: Runs when the client starts its session.
void RandomAgent::onStart(std::string world, std::string role, std::string state)
{
    //has started its session as the {role} in world \"{world['name']}\"."
    std::cout << *this << " has started its session as the " << role 
    << " in world \"" << world << "\"." << std::endl;
}

// Optional: Runs each time the client sees a story world update, whether
//  or not it is the client's turn.
void RandomAgent::onUpdate(std::string status)
{
}

// Required: Runs each time the world updates and it is the client's turn.
int RandomAgent::onChoice(std::string status)
{
    // lots o work to be done here
    return -1;
}

// Optional: Runs when the story reaches an ending.
void RandomAgent::onEnd(std::string ending)
{
    std::cout << *this << " has reached an ending: \"" << ending << "\"" << std::endl;
}

// Optional: Runs when the client stops normally by the `close` method or
//  because the story ended. Does not run if client crashes.
void RandomAgent::onClose()
{
    std::cout << *this << " had closed." << std::endl;
}

// Optional: Runs when the session stops.
void RandomAgent::onStop(std::string message)
{
    if (message == "") {
        std::cout << *this << " has stopped." << std::endl;
    }
    else {
        std::cout << *this << " has stopped: \"" << message << "\"" << std::endl;
    }
}

// Optional: Run when the client disconnects from the server.
void RandomAgent::onDisconnect(std::string)
{
    std::cout << *this << " has disconnected." << std::endl;
}

std::ostream &operator<<(std::ostream &os, const RandomAgent &a)
{
    os << a.toString();
    return os;
}
