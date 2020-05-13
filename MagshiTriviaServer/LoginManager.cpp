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
	if (this->m_database->doesUserExist(username) and this->m_database->doesPasswordMatch(password)) { // this is a very stupid way to validate and terrible design, pretty sure it also doesn't work properly but could be fixed with 2 lines of code.
		this->m_loggedUsers.push_back(LoggedUser(username)); // basically what it does is check if there is an account with the username and check if there is an account with that password, not if there is an account with both.
	}
}

void LoginManager::signup(std::string username, std::string password, std::string email) {
	this->m_database->addNewUser(username, password, email);
}

void LoginManager::logout(std::string username) {
	this->m_loggedUsers.erase(std::remove_if(this->m_loggedUsers.begin(), this->m_loggedUsers.end(), [&](auto user) {return user.getUsername() == username; }));
}
