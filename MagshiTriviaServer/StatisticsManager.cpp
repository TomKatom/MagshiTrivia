#include "StatisticsManager.hpp"

StatisticsManager::StatisticsManager(IDatabase* db) {
	this->m_database = db;
}
UserStatistics StatisticsManager::getStatistics(std::string name) {
	UserStatistics response;
	response.numOfPlayerGames = this->m_database->getNumOfPlayerGames(name);
	response.numberOfTotalAnswers = this->m_database->getNumOfTotalAnswers(name);
	response.numOfCorrectAnswers = this->m_database->getNumOfCorrectAnswers(name);
	response.averageTimeForAnswer = this->m_database->getAverageAnswerTime(name);
	return response;
}

void StatisticsManager::updateStatistics(PlayerResults results, bool won) {
	this->m_database->updateStatistics(results, won);
}

std::vector<LeaderboardEntry> StatisticsManager::getLeaderboard() {
	return this->m_database->getLeaderboard();
}