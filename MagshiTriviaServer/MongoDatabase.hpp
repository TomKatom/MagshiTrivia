#define _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING
#include "IDatabase.hpp"
#include <vector>
#include <string>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include "LoggedUser.hpp"
#include "GameData.hpp"
#include <map>

class MongoDatabase : public IDatabase {
public:
	MongoDatabase();
	bool doesUserExist(std::string username) override;
	bool doesPasswordMatch(std::string username, std::string password) override;
	void addNewUser(std::string username, std::string password, std::string email) override;

	std::vector<Question*>& getQuestions(int x) override;
	float getAverageAnswerTime(std::string name) override;
	int getNumOfCorrectAnswers(std::string name) override;
	int getNumOfTotalAnswers(std::string name) override;
	int getNumOfPlayerGames(std::string name) override;
	void updateStatistics(PlayerResults results, bool won) override;
	std::vector<LeaderboardEntry> getLeaderboard() override;
private:
	mongocxx::database _db;
	mongocxx::client* _client;

};