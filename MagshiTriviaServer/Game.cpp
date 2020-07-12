#pragma once
#include "Game.hpp"

Game::Game(std::vector<Question> questions, Room room, int id) {
	this->questions = questions;
	this->id = id;
	for (auto player : room.getAllUsers()) {
		this->m_players[player] = GameData( this->questions[0], 0, 0, 0 );
	}
	this->room = room;
}

Question Game::getQuestionForUser(LoggedUser user) {
	return this->m_players[user].currentQuestion;
}

void Game::SubmitAnswer(LoggedUser user, int answer) {
	if (answer == -1) {
		this->m_players[user].wrongAnswerCount++;
	}
	else {
		if (this->m_players[user].currentQuestion.getPossibleAnswers()[answer] == this->m_players[user].currentQuestion.getCorrectAnswer()) {
			this->m_players[user].correctQuestionCount++;
		}
		else {
			this->m_players[user].wrongAnswerCount++;
		}
	}
	if (this->m_players[user].correctQuestionCount + this->m_players[user].wrongAnswerCount != this->questions.size()) {
		this->m_players[user].currentQuestion = this->questions[this->m_players[user].correctQuestionCount + this->m_players[user].wrongAnswerCount];
	}
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

std::map<LoggedUser, GameData> Game::getPlayers() {
	return this->m_players;
}

Room Game::getRoom() {
	return this->room;
}

bool Game::isFinished() {
	return this->finished;
}

void Game::setFinished(bool state) {
	this->finished = state;
}

std::vector<Question> Game::getQuestions() {
	return this->questions;
}

Game::Game(const Game& game) {
	this->finished = game.finished;
	this->id = game.id;
	this->room = game.room;
	this->m_players = *new std::map<LoggedUser, GameData>(game.m_players);
	this->questions = *new std::vector<Question>();
	for (auto question : game.questions) {
		this->questions.push_back(*new Question(question));
	}
}
