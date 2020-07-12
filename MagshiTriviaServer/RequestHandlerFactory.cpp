#define _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING
#include "RequestHandlerFactory.hpp"
#include "MongoDatabase.hpp"

RequestHandlerFactory::RequestHandlerFactory() {
	this->m_database = new MongoDatabase();
	this->m_loginManager = new LoginManager(this->m_database);
	this->m_statisticsManager = new StatisticsManager(this->m_database);
	this->m_roomManager = new RoomManager();
	this->m_gameManager = new GameManager(this->m_database);
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler() {
	return new LoginRequestHandler(this);
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser user) {
	return new MenuRequestHandler(this, user);
}

RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberHandler(LoggedUser user) {
	return new RoomMemberRequestHandler(this, user);
}

RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminHandler(LoggedUser user) {
	return new RoomAdminRequestHandler(this, user);
}

GameRequestHandler* RequestHandlerFactory::createGameRequestHandler(LoggedUser user, Game game) {
	return new GameRequestHandler(this, user, game);
}


LoginManager& RequestHandlerFactory::getLoginManager() {
	return *this->m_loginManager;
}
 
RoomManager& RequestHandlerFactory::getRoomManager() {
	return *this->m_roomManager;
}

StatisticsManager& RequestHandlerFactory::getStatisticManager() {
	return *this->m_statisticsManager;
}

GameManager& RequestHandlerFactory::getGameManager() {
	return *this->m_gameManager;
}



