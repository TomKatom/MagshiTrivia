#pragma once
#include "Game.hpp"
#include "IDatabase.hpp"
#include "Room.hpp"

class GameManager {
private:
	IDatabase* m_database;
	std::vector<Game*> games;
	int currGameId;
public:
	GameManager(IDatabase* m_database);
	Game* createGame(Room* room);
	void deleteRoom(Game* game);
	Game* findGame(int roomId);
};
