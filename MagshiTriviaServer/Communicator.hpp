#pragma once
#include <map>
#include <mutex>
#include <SFML/Network.hpp>
#include "IRequestHandler.hpp"
#include "RequestHandlerFactory.hpp"
#include "LoginRequestHandler.hpp"

class Communicator
{
public:
	void startHandleRequests();


private:
	void bindAndListen();
	void handleNewClient(sf::TcpSocket* client);

	std::mutex _clientLock;
	std::map<sf::TcpSocket*, IRequestHandler*> m_clients;
	RequestHandlerFactory m_handlerFactory;

};

