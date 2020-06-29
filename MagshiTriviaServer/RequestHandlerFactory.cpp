#define _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING
#include "RequestHandlerFactory.hpp"
#include "MongoDatabase.hpp"

RequestHandlerFactory::RequestHandlerFactory() {
	this->m_database = new MongoDatabase();
	this->m_loginManager = new LoginManager(this->m_database);
	this->m_statisticsManager = new StatisticsManager(this->m_database);
}

LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler() {
	return new LoginRequestHandler(this);
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(LoggedUser user) {
	return new MenuRequestHandler(this, user);
}

LoginManager& RequestHandlerFactory::getLoginManager() {
	return *this->m_loginManager;
}
 
RoomManager& RequestHandlerFactory::getRoomManager() {
	return this->m_roomManager;
}

StatisticsManager& RequestHandlerFactory::getStatisticManager() {
	return *this->m_statisticsManager;
}



