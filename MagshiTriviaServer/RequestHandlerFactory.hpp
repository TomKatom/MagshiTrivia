#pragma once
#include "LoginManager.hpp"
#include "LoginRequestHandler.hpp"
#include "MenuRequestHandler.hpp"
class RequestHandlerFactory
{
public:
	RequestHandlerFactory() { };
	LoginRequestHandler* createLoginRequestHandler() { return new LoginRequestHandler; }
	MenuRequestHandler* createMenuRequestHandler() { return new MenuRequestHandler; }

	//V2
	

	//LoginManager& getLoginManager();

	//v3



private:
	LoginManager m_loginManager;

};

