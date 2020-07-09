#define _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING
#include <SFML/Network.hpp>
#include <thread>
#include <vector>
#include "Server.hpp"
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <iostream>

#include <nlohmann/json.hpp>

using namespace nlohmann;


int main()
{
	mongocxx::instance instance{}; 
	Server server;
	server.run();
	return 0;
}

