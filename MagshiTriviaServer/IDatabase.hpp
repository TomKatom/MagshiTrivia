#pragma once
#include <string>

class IDatabase {
public:
	virtual ~IDatabase() = default;
	virtual bool doesUserExist(std::string username) = 0;
	virtual bool doesPasswordMatch(std::string username, std::string password) = 0;
	virtual void addNewUser(std::string username, std::string password, std::string email) = 0;
};