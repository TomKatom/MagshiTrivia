#include "Communicator.hpp"
#include <thread>

#define MAX_SIZE 1024

void Communicator::startHandleRequests() {
	sf::TcpListener listener;
	std::vector<std::thread*> threads;
	std::thread* match;
	bool createdListeneSock = true;

	if (listener.listen(5000) != sf::Socket::Done)
		createdListeneSock = false;

	while (createdListeneSock)
	{
		sf::TcpSocket* client = new sf::TcpSocket;

		if (listener.accept(*client) != sf::Socket::Done) continue;
			//throw std::exception("Can not accept connection");

		LoginRequestHandler * loginHandler = m_handlerFactory.createLoginRequestHandler();
		std::unique_lock<std::mutex> clientLockGuard(this->_clientLock);
		this->m_clients.insert({ client, static_cast<IRequestHandler*> (  loginHandler) });
		clientLockGuard.unlock();

		match = new std::thread(&Communicator::handleNewClient,this, client);
		match->detach();
		threads.push_back(match);
	}

	for (auto thread : threads)
	{
		delete thread;
	}
}

void Communicator::handleNewClient(sf::TcpSocket* client) {

	char data[MAX_SIZE];
	std::size_t received;

	while (true) {
		if (client->receive(data, MAX_SIZE, received) != sf::Socket::Done)	{
		}
		else {

			if (client->send("Hello client" , 13) != sf::Socket::Done)
			{

			}
			/*std::lock_guard<std::mutex> clientLockGuard(this->_clientLock);
			if (this->m_clients.find(client)->second->isRequestValid()) {

			}*/
		}
	}

}