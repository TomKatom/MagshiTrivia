#pragma once
#include <vector>
#include "LoggedUser.hpp"
#include "IDatabase.hpp"

class LoginManager
{
public:
	LoginManager(IDatabase* db);
	~LoginManager();
	LoggedUser* login(std::string username, std::string password);
	void signup(std::string username, std::string password, std::string email);
	void logout(std::string username);
	std::string getLastUser();

private: 
	std::vector<LoggedUser*> m_loggedUsers;
	std::string lastUser;
	IDatabase* m_database;
};

