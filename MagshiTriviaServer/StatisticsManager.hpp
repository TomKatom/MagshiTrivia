#pragma once
#include "IDatabase.hpp"
#include "ProtocolStructs.hpp"
#include <string>
#include "GameData.hpp"

class StatisticsManager {
public:
	StatisticsManager(IDatabase* db);
	UserStatistics getStatistics(std::string name);
	void updateStatistics(std::pair <LoggedUser, GameData> user);
private:
	IDatabase* m_database;
};