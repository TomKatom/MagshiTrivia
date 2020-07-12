#pragma once
#include "GameData.hpp"
#include "LoggedUser.hpp"
#include "Room.hpp"
#include <vector>
#include <map>

class Game {
private:
	std::vector<Question> questions;
	std::map<LoggedUser, GameData> m_players;
	int id;
	Room room;
	bool finished;
public:
	Game() = default;
	Game(const Game& game);
	Game(std::vector<Question> questions, Room room, int id);
	bool operator==(Game other);
	Question getQuestionForUser(LoggedUser user);
	void SubmitAnswer(LoggedUser user, int answer);
	void removePlayer(LoggedUser user);
	std::map<LoggedUser, GameData> getPlayers();
	Room getRoom();
	bool isFinished();
	void setFinished(bool state);
	std::vector<Question> getQuestions();
};
