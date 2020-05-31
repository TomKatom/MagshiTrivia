#include "Room.hpp"
#include <algorithm>

void Room::addUser(LoggedUser user) {
	if (std::find_if(this->m_users.begin(), this->m_users.end(), [&](auto user) {return user.getUsername() == username; }) == this->m_users.end()) {
		this->m_users.push_back(user);
	}
	else {
		throw std::exception("User is already in the room.");
	}
}

void Room::removeUser(LoggedUser) {
	this->m_users.erase(std::remove_if(this->m_users.begin(), this->m_users.end(), [&](auto user) {return user.getUsername() == username; }));
}

std::list<LoggedUser> Room::getAllUsers() const {
	std::list<LoggedUser> users;
	for (auto user : this->m_users) {
		users.push_back(user);
	}
	return users;
}