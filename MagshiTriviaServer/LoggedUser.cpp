#pragma once
#include "LoggedUser.hpp"

LoggedUser::LoggedUser(std::string username) {
	this->m_username = username;
}

std::string LoggedUser::getUsername() {
	return this->m_username;
}
