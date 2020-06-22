#include "RequestHandlerFactory.hpp"

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler() {
	return new LoginRequestHandler(this);
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler() {
	return new MenuRequestHandler(this);
}

LoginManager& RequestHandlerFactory::getLoginManager() {
	return this->m_loginManager;
}
 
RoomManager& RequestHandlerFactory::getRoomManager() {
	return this->m_roomManager;
}



