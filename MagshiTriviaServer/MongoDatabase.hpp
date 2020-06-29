#define _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING
#include "IDatabase.hpp"
#include <string>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>

class MongoDatabase : public IDatabase {
public:
	MongoDatabase();
	bool doesUserExist(std::string username) override;
	bool doesPasswordMatch(std::string username, std::string password) override;
	void addNewUser(std::string username, std::string password, std::string email) override;

	virtual std::list<Question> getQuestions(int x) override;
	virtual float getAverageAnswerTime(std::string name) override;
	virtual int getNumOfCorrectAnswers(std::string name) override;
	virtual int getNumOfTotalAnswers(std::string name) override;
	virtual int getNumOfPlayerGames(std::string name) override;
private:
	mongocxx::database _db;
	mongocxx::client* _client;

};