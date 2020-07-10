#pragma once
#include "Game.hpp"

Game::Game(std::vector<Question> questions, Room room, int id) {
	this->questions = questions;
	this->id = id;
	for (auto player : room.getAllUsers()) {
		this->m_players[player] = GameData( this->questions[0], 0, 0, 0 );
	}
}

Question Game::getQuestionForUser(LoggedUser user) {
	return this->m_players[user].currentQuestion;
}

void Game::SubmitAnswer(LoggedUser user, int answer) {
	if (this->m_players[user].currentQuestion.getPossibleAnswers()[answer] == this->m_players[user].currentQuestion.getCorrectAnswer()) {
		this->m_players[user].correctQuestionCount++;
	}
	else {
		this->m_players[user].wrongAnswerCount++;
	}
	this->m_players[user].currentQuestion = this->questions[this->m_players[user].correctQuestionCount + this->m_players[user].wrongAnswerCount];
}

void Game::removePlayer(LoggedUser user) {
	if (this->m_players.find(user) != this->m_players.end()) {
		this->m_players.erase(user);
	}
	else {
		throw std::string("User isn't in the game.");
	}
}
bool Game::operator==(Game other) {
	return this->id == other.id;
}
