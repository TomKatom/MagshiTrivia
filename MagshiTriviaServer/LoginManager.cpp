#include "LoginManager.hpp"
#include <algorithm>
#include "AlreadyLoggedInException.hpp"

LoginManager::LoginManager(IDatabase* db) {
	this->m_database = db;
}
LoginManager::~LoginManager() {
	delete this->m_database;
}

LoggedUser* LoginManager::login(std::string username, std::string password) {
	LoggedUser* user = nullptr;
	if (std::find_if(this->m_loggedUsers.begin(), this->m_loggedUsers.end(), [&](auto user) {return user->getUsername() == username; }) == this->m_loggedUsers.end()) {
		if (this->m_database->doesPasswordMatch(username, password)) { 
			user = new LoggedUser(username);
			this->m_loggedUsers.push_back(user); 
			return user;
		}
		else {
			throw std::exception("User doesn't exist.");
		}
	}
	else {
		throw AlreadyLoggedInException();
	}
	return nullptr;
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
	this->m_loggedUsers.erase(std::remove_if(this->m_loggedUsers.begin(), this->m_loggedUsers.end(), [&](auto user) {return user->getUsername() == username; }));
}
