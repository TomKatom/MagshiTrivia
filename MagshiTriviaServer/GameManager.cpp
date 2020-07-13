#include "GameManager.hpp"
#include <algorithm>

GameManager::GameManager(IDatabase* m_database) {
	this->currGameId = 1;
	this->m_database = m_database;
}
Game* GameManager::createGame(Room* room) {
	Game* newGame = new Game(this->m_database->getQuestions(room->getQuestionsCount()), room, currGameId);
	this->currGameId++;
	this->games.push_back(newGame);
	return newGame;
}

void GameManager::deleteRoom(Game* game) {
	if(std::find(this->games.begin(), this->games.end(), game) != this->games.end()) {
		this->games.erase(std::remove(this->games.begin(), this->games.end(), game), this->games.end());
	}
	else {
		throw std::string("Game doesn't exit.");
	}
}

Game* GameManager::findGame(int roomId) {
	for (auto game : games) {
		if (game->getRoom()->getID() == roomId) {
			return game;
		}
	}
}