#pragma once
#include <string>

class LoggedUser {
public:
	LoggedUser() = default;
	LoggedUser(std::string username);
	std::string getUsername();

private:
	std::string m_username;
};
