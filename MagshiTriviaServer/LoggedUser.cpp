#pragma once
#include "LoggedUser.hpp"

LoggedUser::LoggedUser(std::string username) {
	this->m_username = username;
}

std::string LoggedUser::getUsername() const {
	return this->m_username;
}

int LoggedUser::getRoomId() const {
	return this->roomId;
}

void LoggedUser::setRoomId(int id) {
	this->roomId = id;
}

bool LoggedUser::operator<(const LoggedUser& other) const {
	return this->m_username < other.m_username;
}

bool LoggedUser::operator==(const LoggedUser& other) const {
	return this->m_username == other.m_username;
}