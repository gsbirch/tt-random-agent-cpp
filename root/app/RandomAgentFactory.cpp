#include "RandomAgentFactory.h"
#include <iostream>

RandomAgentFactory::RandomAgentFactory(const std::string &url, const int port)
: url(url), port(port)
{
    
}

std::string RandomAgentFactory::toString() const
{
    return "Random Agent Factory";
}

void RandomAgentFactory::onStart() const
{
    std::cout << *this << " has started." << std::endl;
}

std::unique_ptr<tt::Client> RandomAgentFactory::create() const
{
    return std::make_unique<RandomAgent>(url, port);
}

void RandomAgentFactory::onClose() const
{
    std::cout << *this << " has been closed." << std::endl;
}

void RandomAgentFactory::onStop() const
{
    std::cout << *this << " has stopped." << std::endl;
}

std::ostream& operator<<(std::ostream& os, const RandomAgentFactory& a) {
    os << a.toString();
    return os;
}