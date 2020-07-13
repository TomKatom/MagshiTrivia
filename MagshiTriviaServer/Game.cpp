#pragma once
#include "Game.hpp"
#include <algorithm>

Game::Game(std::vector<Question*> questions, Room* room, int id) {
	this->questions = questions;
	this->id = id;
	for (auto player : room->getAllUsers()) {
		this->m_players[player] = new GameData( this->questions[0], 0, 0, 0 );
	}
	this->room = room;
}

Question& Game::getQuestionForUser(LoggedUser* user) {
	return *this->m_players[user]->currentQuestion;
}

void Game::SubmitAnswer(RequestInfo request, LoggedUser* user, int answer) {
	if (answer == -1) {
		for (auto player : this->m_players) {
			if (player.first == user) {
				player.second->wrongAnswerCount++;
			}
		}
	}
	else {
		if (this->m_players[user]->currentQuestion->getPossibleAnswers()[answer] == this->m_players[user]->currentQuestion->getCorrectAnswer()) {
			this->m_players[user]->correctQuestionCount++;
		}
		else {
			this->m_players[user]->wrongAnswerCount++;
		}
	}
	if (this->m_players[user]->correctQuestionCount + this->m_players[user]->wrongAnswerCount != this->questions.size()) {
		this->m_players[user]->currentQuestion = this->questions[this->m_players[user]->correctQuestionCount + this->m_players[user]->wrongAnswerCount];
	}
}

void Game::removePlayer(LoggedUser* user) {
	if (this->m_players.find(user) != this->m_players.end()) {
		this->m_players.erase(user);
	}
	else {
		throw std::string("User isn't in the game.");
	}
}
bool Game::operator==(const Game& other) const {
	return this->id == other.id;
}

std::map<LoggedUser*, GameData*>& Game::getPlayers() {
	return this->m_players;
}

Room* Game::getRoom() {
	return this->room;
}

bool Game::isFinished() {
	return this->finished;
}

void Game::setFinished(bool state) {
	this->finished = state;
}

std::vector<Question*>& Game::getQuestions() {
	return this->questions;
}

std::vector<PlayerResults>& Game::getResults() {
	return this->gameResults;
}

void Game::generateResults() {
	std::vector<PlayerResults> results;
	for (auto player : this->m_players) {
		PlayerResults result = { player.first->getUsername(), player.second->correctQuestionCount, player.second->wrongAnswerCount, player.second->averageAnswerTime };
		results.push_back(result);
	}
	std::sort(results.begin(), results.end());
	std::reverse(results.begin(), results.end());
	this->gameResults = results;
}
