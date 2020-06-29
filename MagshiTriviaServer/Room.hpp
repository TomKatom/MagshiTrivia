#pragma once
#include <string>
#include <vector>
#include "LoggedUser.hpp"
#include <list>
class Room {
public:
	Room() = default;
	Room(int id, std::string name, int maxPlayers, unsigned int timePerQuestion, int questionCount);
	void addUser(LoggedUser user);
	void removeUser(LoggedUser user);
	int getID();
	std::list<LoggedUser> getAllUsers() const;
	std::string getName();
	bool getState();
	void setActive(bool active);
	int getMaxPlayers() const;
	unsigned int getTimePerQuestion() const;
	int getQuestionsCount() const;

private:
	int _id;
	std::string _name;
	int _maxPlayers;
	unsigned int _timePerQuestion;
	bool _isActive;
	int _questionsCount;
	std::vector<LoggedUser> m_users;
};