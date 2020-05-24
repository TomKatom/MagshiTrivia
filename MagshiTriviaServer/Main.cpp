#define _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING
#include <SFML/Network.hpp>
#include <thread>
#include <vector>
#include "Server.hpp"
#include "MongoDatabase.hpp"
#include <iostream>

int main()
{
	Server server;
	server.run();
	return 0;
}

