#define _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING
#include "LoginManager.hpp"
#include "MongoDatabase.hpp"
#include <algorithm>

LoginManager::LoginManager() {
	this->m_database = new MongoDatabase();
}
LoginManager::~LoginManager() {
	delete this->m_database;
}

void LoginManager::login(std::string username, std::string password) {
	if (std::find_if(this->m_loggedUsers.begin(), this->m_loggedUsers.end(), [&](auto user) {return user.getUsername() == username; }) == this->m_loggedUsers.end()) {

		if (this->m_database->doesPasswordMatch(username, password)) { 
			this->m_loggedUsers.push_back(LoggedUser(username)); 
		}
		else {
			throw std::exception("User doesn't exist.");

		}
	}
	else {
		throw std::exception("User already logged in.");
	}
}

void LoginManager::signup(std::string username, std::string password, std::string email) {
	if (!this->m_database->doesUserExist(username)) {
		this->m_database->addNewUser(username, password, email);
	}
	else {
		throw std::exception("User already exists.");
	}
}

void LoginManager::logout(std::string username) {
	this->m_loggedUsers.erase(std::remove_if(this->m_loggedUsers.begin(), this->m_loggedUsers.end(), [&](auto user) {return user.getUsername() == username; }));
}
