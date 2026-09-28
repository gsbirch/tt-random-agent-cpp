#include "RandomAgent.h"
#include "RandomAgentFactory.h"

#include <iostream>
#include <string>
#include <cxxopts.hpp>

std::string rpad(const std::string& str) {
    return str + std::string(std::max(0, 16 - (int)str.length()), ' ');
}

/**
 * Configure and run the agent factory based on Java arguments passed from
 * the terminal.
 * 
 * @param args the arguments passed to this executable
 * @throws Exception if a problem occurs during the factory setup or while
 * it is running
 */
int main(int argc, char *argv[]) {
    /** The name of this agent */
	const std::string NAME = "Tandem Tales Random Agent (C++)";
	
	/** The version number of this agent */
	const std::string VERSION = "0.9.0";
	
	/** The authors of this agent */
	const std::string AUTHORS = "Gage Birchmeier";
	
	/** The full title of the this agent */
	const std::string TITLE = NAME + " v" + VERSION + " by " + AUTHORS;
	
	/** The key used to print the usage instructions */
	const std::string HELP_KEY = "help";
	
	/** The key used to specify the server to connect to */
	const std::string URL_KEY = "url";
	
	/** The key used to specify the network port to the server connect on */
	const std::string PORT_KEY = "port";
	
	/** Instructions for how to use this agent */
	const std::string USAGE = 
		rpad("-" + HELP_KEY) + "Print usage information.\n" +
		rpad("-" + URL_KEY + " <string>") + "Specifies the URL of the server (defaults to \"" + RandomAgent::DEFAULT_URL + "\").\n" +
		rpad("-" + PORT_KEY + " <number>") + "Specifies the network port of the server (defaults to " +  std::to_string(RandomAgent::DEFAULT_PORT) + ").";
	
	std::cout << TITLE << std::endl;

	// Parse args
	cxxopts::Options options("tt-random-agent", "A sample Tandem Tales agent written in C++");
	options.add_options()
		(HELP_KEY, 	"Help")
		(URL_KEY,	"URL",	cxxopts::value<std::string>())
		(PORT_KEY, 	"Port",	cxxopts::value<int>());
	auto result = options.parse(argc, argv);

	// Help
	if (result.count(HELP_KEY)) {
		std::cout << USAGE << std::endl;
		return -1;
	}
	
	// Network Settings
	std::string url = RandomAgent::DEFAULT_URL;
	int port = RandomAgent::DEFAULT_PORT;
	if (result.count(URL_KEY))
		url = result[URL_KEY].as<std::string>();
	if (result.count(PORT_KEY))
		url = result[PORT_KEY].as<int>();
		
	// Create Agent Factory
	try {
		RandomAgentFactory factory = RandomAgentFactory(url, port);
		factory.execute();
	}
	catch (...) {
		std::cerr << "Caught an exception" << std::endl;
	}
	return 0;
}