#include <iostream>
#include <string>
#include "RandomAgent.h"
#include "RandomAgentFactory.h"

static std::string rpad(const std::string& str) {
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
int main() {
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

	// Help
	// Arguments arguments = new Arguments(args);
	// if(arguments.contains(HELP_KEY)) {
	// 	System.out.println(USAGE);
	// 	return;
	// }

	// Network Settings
	std::string url = "localhost";
	int port = 9005;
	//arguments.getValue(URL_KEY, RandomAgent.DEFAULT_URL);
	// if(url == "")
	// 	url = RandomAgent.DEFAULT_URL;
	// int port;
	// if(arguments.contains(PORT_KEY))
	// 	port = Integer.parseInt(arguments.getValue(PORT_KEY, Integer.toString(RandomAgent.DEFAULT_PORT)));
	// else
	// 	port = RandomAgent.DEFAULT_PORT;
	// Check for unused arguments.
	// arguments.checkUnused();
	// Create Agent Factory
	try {
		RandomAgentFactory factory = RandomAgentFactory(url, port);
		auto agent = factory.create();
		agent->start();
		tt::Join j;
		j.name = "web";
		j.password = "dummy";
		j.world = "tutorial";
		j.role = tt::Role::PLAYER;
		j.partner = "random";
		agent->sendMessage(j);
	}
	catch (...) {
		std::cerr << "Caught an exception" << std::endl;
	}

	

	std::cerr << "this is an error" << std::endl;
}