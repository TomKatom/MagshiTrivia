#pragma once
#include "LoggedUser.hpp"
#include "Game.hpp"

LoggedUser::LoggedUser(std::string username) {
	this->m_username = username;
}

std::string LoggedUser::getUsername() {
	return this->m_username;
}

int LoggedUser::getRoomId() {
	return this->roomId;
}

void LoggedUser::setRoomId(int id) {
	this->roomId = id;
}

Game LoggedUser::getCurrGame() {
	return *this->currGame;
}

void LoggedUser::setCurrGame(Game game) {
	this->currGame = &game;
}

bool LoggedUser::operator<(const LoggedUser& other) const {
	return this->m_username < other.m_username;
}