#pragma once
#include "IDatabase.hpp"
#include "ProtocolStructs.hpp"
#include <string>
#include <vector>
#include "GameData.hpp"

class StatisticsManager {
public:
	StatisticsManager(IDatabase* db);
	UserStatistics getStatistics(std::string name);
	void updateStatistics(PlayerResults results, bool won);
	std::vector<LeaderboardEntry> getLeaderboard();
private:
	IDatabase* m_database;
};