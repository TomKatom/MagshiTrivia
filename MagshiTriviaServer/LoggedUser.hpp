#pragma once
#include <string>
class Game;

class LoggedUser {
public:
	LoggedUser() = default;
	LoggedUser(std::string username);
	std::string getUsername();
	int getRoomId();
	void setRoomId(int id);
	Game getCurrGame();
	void setCurrGame(Game game);
	bool operator<(const LoggedUser& other) const;

private:
	std::string m_username;
	int roomId;
	Game* currGame;
};
