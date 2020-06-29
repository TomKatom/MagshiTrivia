#pragma once
#include "LoginManager.hpp"
#include "RoomManager.hpp"
#include "LoginRequestHandler.hpp"
#include "MenuRequestHandler.hpp"
#include "StatisticsManager.hpp"

class RequestHandlerFactory
{
public:
	RequestHandlerFactory();
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(LoggedUser user);

	LoginManager& getLoginManager();
	RoomManager& getRoomManager();
	StatisticsManager& getStatisticManager();

private:
	IDatabase* m_database;
	StatisticsManager* m_statisticsManager;
	LoginManager* m_loginManager;
	RoomManager m_roomManager;
};
