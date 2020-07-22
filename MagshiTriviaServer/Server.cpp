#include "Server.hpp"

void Server::run() {
	this->m_communicator.startHandleRequests();
}