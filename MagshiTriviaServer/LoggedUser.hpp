#pragma once
#include <string>

class LoggedUser {
public:
	LoggedUser() = default;
	LoggedUser(std::string username);
	std::string getUsername();
	int getRoomId();
	void setRoomId(int id);

private:
	std::string m_username;
	int roomId;
};
