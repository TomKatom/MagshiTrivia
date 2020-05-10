#include <SFML/Network.hpp>
#include <thread>
#include <vector>
#include "Server.hpp"

int main()
{
	Server server;
	server.run();
	
	return 0;
}

