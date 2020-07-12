#pragma once
#include "LoginManager.hpp"
#include "RoomManager.hpp"
#include "LoginRequestHandler.hpp"
#include "MenuRequestHandler.hpp"
#include "RoomMemberRequestHandler.hpp"
#include "RoomAdminRequestHandler.hpp"
#include "GameRequestHandler.hpp"
#include "StatisticsManager.hpp"
#include "GameManager.hpp"

class RequestHandlerFactory
{
public:
	RequestHandlerFactory();
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler(LoggedUser user);
	RoomMemberRequestHandler* createRoomMemberHandler(LoggedUser user);
	RoomAdminRequestHandler* createRoomAdminHandler(LoggedUser user);
	GameRequestHandler* createGameRequestHandler(LoggedUser user, Game game);


	LoginManager& getLoginManager();
	RoomManager& getRoomManager();
	StatisticsManager& getStatisticManager();
	GameManager& getGameManager();

private:
	IDatabase* m_database;
	StatisticsManager* m_statisticsManager;
	LoginManager* m_loginManager;
	RoomManager* m_roomManager;
	GameManager* m_gameManager;
};
