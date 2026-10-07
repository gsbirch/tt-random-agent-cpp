#include "RandomAgent.h"

#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <chrono>
#include <random>

#include <tt/Role.h>
#include <tt/world/Turn.h>

const double RandomAgent::PASS_PROBABILITY = 0.3;
const double RandomAgent::SUCCEED_PROBABILITY = 0.8;
const long RandomAgent::DEFAULT_DELAY = 5000;
int RandomAgent::nextID = 0;

const std::string RandomAgent::DEFAULT_URL = "localhost";
const int RandomAgent::DEFAULT_PORT = 9005;
//Client.DEFAULT_PORT;

RandomAgent::RandomAgent(const std::string &url, int port, long seed, long delay):
Client("random", "", tt::Role::NONE, "", url, port), delay(delay)
{
    // set the seed for random
    srand(seed);
}

RandomAgent::RandomAgent(const std::string &url, int port, long delay):
RandomAgent(url, port, time(0), delay)
{
}

RandomAgent::RandomAgent(const std::string &url, const int port) : 
RandomAgent(url, port, DEFAULT_DELAY)
{
}

RandomAgent::RandomAgent():
RandomAgent(DEFAULT_URL, DEFAULT_PORT)
{
}

std::string RandomAgent::toString() const
{
    return "Random Agent " + std::to_string(id);
}

// Optional: Runs when the client connects to the server.
void RandomAgent::onConnect(const tt::Connect* connect)
{
    std::cout << *this << " has connected to the server." << std::endl;
}

// Optional: Runs when the client starts its session.
void RandomAgent::onStart(const tt::World* world, tt::Role role, const tt::State* state)
{
    std::cout << *this << " has started its session as the " << role 
    << " in world \"" << world->name << "\"." << std::endl;
}

// Optional: Runs each time the client sees a story world update, whether
//  or not it is the client's turn.
void RandomAgent::onUpdate(const tt::Status* status)
{
    std::cout << *status << std::endl;
}

// Required: Runs each time the world updates and it is the client's turn.
int RandomAgent::onChoice(const tt::Status* status)
{
    int choice = -1;
    // If my partner has proposed a move, accept or reject it.
    if(isProposal(status)) {
        double x = (rand() % 101) * 1.0;
        if(x < SUCCEED_PROBABILITY * 100.0)
            choice = 0; // succeed
        else
            choice = 1; // fail
    }
    // If this is a normal turn and the agent has at least one choice...
    else if(status->getChoices().size() > 1) {
        // Decide if I will act or pass.
        double x = (rand() % 101) * 1.0;
        if (x < PASS_PROBABILITY)
            choice = status->getChoices().size() - 1; // pass
        else
            choice = rand() % (status->getChoices().size() - 1); // act
    }
    // If the agent has no choices, pass.
    else
        choice = 0;
    // Wait a random amount of time before sending the choice.
    try {
        if(delay > 0) {
            std::random_device rd;
            std::mt19937_64 gen(rd());
            std::uniform_int_distribution<long long> dist(0, delay - 1);

            std::this_thread::sleep_for(std::chrono::milliseconds(dist(gen)));
        }
    }
    catch(...) {
        // If interrupted, return choice immediately.
    }
    // Return the choice.
	std::cout << *this << " chooses: \"" << status->getChoices()[choice]->description << "\"." << std::endl;
    return choice;
}

// Optional: Runs when the story reaches an ending.
void RandomAgent::onEnd(const tt::Ending *ending)
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
void RandomAgent::onStop(const std::string& message)
{
    if (message == "") {
        std::cout << *this << " has stopped." << std::endl;
    }
    else {
        std::cout << *this << " has stopped: \"" << message << "\"" << std::endl;
    }
}

// Optional: Run when the client disconnects from the server.
void RandomAgent::onDisconnect()
{
    std::cout << *this << " has disconnected." << std::endl;
}

bool RandomAgent::isProposal(const tt::Status *status)
{
    auto choices = status->getChoices();
    return choices.size() == 2 &&
        choices[0]->type == tt::Turn::Type::SUCCEED &&
        choices[1]->type == tt::Turn::Type::FAIL;
}
