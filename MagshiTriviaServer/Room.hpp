#include <string>
#include <vector>
#include "LoggedUser.hpp"
#include <list>
class Room {
public:
	void addUser(LoggedUser user);
	void removeUser(LoggedUser user);
	std::list<LoggedUser> getAllUsers() const;
private:
	int _id;
	std::string _name;
	int _maxPlayers;
	unsigned int _timePerQuestion;
	bool _isActive;
	std::vector<LoggedUser> m_users;
};