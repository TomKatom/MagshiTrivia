#pragma once
#include "LoginManager.hpp"
#include "LoginRequestHandler.hpp"
class RequestHandlerFactory
{
public:

	LoginRequestHandler* createLoginRequestHandler() { return nullptr; }
	//LoginManager& getLoginManager();


private:
	LoginManager m_loginManager;


};

