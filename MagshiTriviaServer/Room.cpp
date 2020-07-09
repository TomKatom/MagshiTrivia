#include "Room.hpp"
#include <algorithm>


Room::Room(int id, std::string name, int maxPlayers, unsigned int timePerQuestion, int questionCount) {
	this->_id = id;
	this->_name = name;
	this->_maxPlayers = maxPlayers;
	this->_timePerQuestion = timePerQuestion;
	this->_questionsCount = questionCount;
	this->_isActive = false;
}

void Room::addUser(LoggedUser user) {
	if (std::find_if(this->m_users.begin(), this->m_users.end(), [&](auto username) {return user.getUsername() == username.getUsername(); }) == this->m_users.end()) {
		this->m_users.push_back(user);
	}
	else {
		throw std::exception("User is already in the room.");
	}
}


void Room::removeUser(LoggedUser user) {
	this->m_users.erase(std::remove_if(this->m_users.begin(), this->m_users.end(), [&](auto username) {return user.getUsername() == username.getUsername(); }));
}

std::list<LoggedUser> Room::getAllUsers() const {
	std::list<LoggedUser> users;
	for (auto user : this->m_users) {
		users.push_back(user);
	}
	return users;
}

void Room::setActive(bool active) {
	this->_isActive = active;
}

std::string Room::getName() {
	return this->_name;
}

bool Room::getState() {
	return this->_isActive;
}

int Room::getMaxPlayers() const {
	return this->_maxPlayers;
}

unsigned int Room::getTimePerQuestion() const {
	return this->_timePerQuestion;
}

int Room::getQuestionsCount() const {
	return this->_questionsCount;
}
int Room::getID() {
	return this->_id;
}