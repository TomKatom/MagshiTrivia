#pragma once
#include <string>

class LoggedUser {
public:
	LoggedUser() = default;
	LoggedUser(std::string username);
	std::string getUsername() const;
	int getRoomId() const;
	void setRoomId(int id);
	bool operator<(const LoggedUser& other) const;
	bool operator==(const LoggedUser& other) const;

private:
	std::string m_username;
	int roomId;
};
