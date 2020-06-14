#pragma once
#include <string>
struct RoomData {
	std::string name;
	int maxPlayers; 
	unsigned int timePerQuestion;
	int questionsCount;
};