#pragma once
#include <vector>
#include "LoggedUser.hpp"
#include "IDatabase.hpp"

class LoginManager
{
public:
	LoginManager();
	~LoginManager();
	void login(std::string username, std::string password);
	void signup(std::string username, std::string password, std::string email);
	void logout(std::string username);

private: 
	std::vector<LoggedUser> m_loggedUsers;
	IDatabase* m_database;
};

