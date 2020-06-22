#pragma once
#include "LoginManager.hpp"
#include "RoomManager.hpp"
#include "LoginRequestHandler.hpp"
#include "MenuRequestHandler.hpp"

class RequestHandlerFactory
{
public:
	RequestHandlerFactory() { };
	LoginRequestHandler* createLoginRequestHandler();
	MenuRequestHandler* createMenuRequestHandler();

	LoginManager& getLoginManager();
	RoomManager& getRoomManager();

private:
	LoginManager m_loginManager;
	RoomManager m_roomManager;
};

