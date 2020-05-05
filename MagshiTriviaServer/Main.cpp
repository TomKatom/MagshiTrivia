#include <SFML/Network.hpp>
#include <thread>
#include <vector>
#include <nlohmann/json.hpp>
#include "Server.hpp"

int main()
{
	Server server;
	server.run();
	
	return 0;
}

