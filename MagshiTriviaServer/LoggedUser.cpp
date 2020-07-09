#pragma once
#include "LoggedUser.hpp"

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