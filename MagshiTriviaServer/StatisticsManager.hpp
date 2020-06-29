#pragma once
#include "IDatabase.hpp"
#include "ProtocolStructs.hpp"
#include <string>

class StatisticsManager {
public:
	StatisticsManager(IDatabase* db);
	UserStatistics getStatistics(std::string name);
private:
	IDatabase* m_database;
};