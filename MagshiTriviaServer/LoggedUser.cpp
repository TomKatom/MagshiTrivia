#pragma once
#include "LoggedUser.hpp"

LoggedUser::LoggedUser(std::string username) {
	this->m_username = username;
	this->leftGame = false;
}

std::string LoggedUser::getUsername() const {
	return this->m_username;
}

int LoggedUser::getRoomId() const {
	return this->roomId;
}

bool LoggedUser::getLeftGame() const
{
	return this->leftGame;
}

void LoggedUser::setRoomId(int id) {
	this->roomId = id;
}

void LoggedUser::setLeftGame(bool leftGame) {
	this->leftGame = leftGame;
}

bool LoggedUser::operator<(const LoggedUser& other) const {
	return this->m_username < other.m_username;
}

bool LoggedUser::operator==(const LoggedUser& other) const {
	return this->m_username == other.m_username;
}