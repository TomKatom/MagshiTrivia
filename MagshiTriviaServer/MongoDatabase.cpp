#define _SILENCE_CXX17_ITERATOR_BASE_CLASS_DEPRECATION_WARNING
#include "MongoDatabase.hpp"
#include <cstdint>
#include <iostream>
#include <vector>
#include <bsoncxx/json.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/array.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/pipeline.hpp>
#include "nlohmann/json.hpp"
#include <algorithm>
#include <random>

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

using std::string;
using namespace nlohmann;

MongoDatabase::MongoDatabase() {
	this->_client = new mongocxx::client(mongocxx::uri{});
	this->_db = (*_client)["Trivia"];
}

void MongoDatabase::addNewUser(string name, string password, string email) {
	mongocxx::collection users = this->_db["users"];
	auto builder = bsoncxx::builder::stream::document{};
	bsoncxx::document::value doc_value = builder
		<< "username" << name
		<< "password" << password
		<< "email" << email
		<< "gameCount" << 0
		<< "correctAnswerCount" << 0
		<< "answerCount" << 0
		<< "wrongAnswerCount" << 0
		<< "averageTimeForAnswer" << 0.0
		<< "wins" << 0
		<< bsoncxx::builder::stream::finalize;
	auto result = users.insert_one(doc_value.view());
}
bool MongoDatabase::doesPasswordMatch(string username, string password) {
	mongocxx::collection users = this->_db["users"];
	auto result = users.find_one(document{} << "username" << username << "password" << password << finalize);
	return result ? true : false;
}
bool MongoDatabase::doesUserExist(string username) {
	mongocxx::collection users = this->_db["users"];
	auto result = users.find_one(document{} << "username" << username << finalize);
	return result ? true : false;
}


std::vector<Question*>& MongoDatabase::getQuestions(int x)
{
	mongocxx::collection questions = this->_db["questions"];
	mongocxx::cursor result = questions.aggregate(mongocxx::pipeline().sample(x));
	std::vector<Question*>* questionList = new std::vector<Question*>();
	auto rng = std::default_random_engine{};
	for (auto question : result) {
		json j = json::parse(bsoncxx::to_json(question));
		std::vector<string> possibleAnswers = j["incorrect_answers"];
		possibleAnswers.push_back(j["correct_answer"]);
		std::shuffle(possibleAnswers.begin(), possibleAnswers.end(), rng);
		std::vector<string>* newAnswers = new std::vector<string>(possibleAnswers);
		Question* temp = new Question(j["question"], j["correct_answer"], *newAnswers);
		questionList->push_back(temp);
	}
	return *questionList;
}
float MongoDatabase::getAverageAnswerTime(std::string name)
{
	mongocxx::collection users = this->_db["users"];
	auto result = users.find_one(document{} << "username" << name << finalize);
	json j = json::parse(bsoncxx::to_json(result->view()));
	return j["averageTimeForAnswer"];
}
int MongoDatabase::getNumOfCorrectAnswers(std::string name)
{
	mongocxx::collection users = this->_db["users"];
	auto result = users.find_one(document{} << "username" << name << finalize);
	json j = json::parse(bsoncxx::to_json(result->view()));
	return j["correctAnswerCount"];
}
int MongoDatabase::getNumOfTotalAnswers(std::string name)
{
	mongocxx::collection users = this->_db["users"];
	auto result = users.find_one(document{} << "username" << name << finalize);
	json j = json::parse(bsoncxx::to_json(result->view()));
	return j["answerCount"];
}
int MongoDatabase::getNumOfPlayerGames(std::string name)
{
	mongocxx::collection users = this->_db["users"];
	auto result = users.find_one(document{} << "username" << name << finalize);
	json j = json::parse(bsoncxx::to_json(result->view()));
	return j["gameCount"];
}

void MongoDatabase::updateStatistics(PlayerResults results, bool won) {
	double newAverageTimeForAnswer = (results.averageAnswerTime + this->getAverageAnswerTime(results.username) / 2);
	int newNumOfCorrectAnswers = results.correctAnswerCount + this->getNumOfCorrectAnswers(results.username);
	int newNumOfTotalAnswers = results.correctAnswerCount + results.wrongAnswerCount + this->getNumOfTotalAnswers(results.username);
	int newNumOfPlayerGames = this->getNumOfPlayerGames(results.username) + 1;
	mongocxx::collection users = this->_db["users"];
	if (!won) {
		users.update_one(document{} << "username" << results.username << finalize, document{} << "$set" << open_document
		<< "averageTimeForAnswer" << newAverageTimeForAnswer
		<< "correctAnswerCount" << newNumOfCorrectAnswers
		<< "answerCount" << newNumOfTotalAnswers
		<< "gameCount" << newNumOfPlayerGames << close_document << finalize);
	}
	else {
		int currWins = json::parse(bsoncxx::to_json(users.find_one(document{} << "username" << results.username << finalize)->view()))["wins"];
		users.update_one(document{} << "username" << results.username << finalize, document{} << "$set" << open_document
		<< "averageTimeForAnswer" << newAverageTimeForAnswer
		<< "correctAnswerCount" << newNumOfCorrectAnswers
		<< "answerCount" << newNumOfTotalAnswers
		 << "wins"  << currWins+1
		<< "gameCount" << newNumOfPlayerGames 
		<< close_document << finalize);

	}
}

std::vector<LeaderboardEntry> MongoDatabase::getLeaderboard() {
	std::vector<LeaderboardEntry>* players = new std::vector<LeaderboardEntry>();
	mongocxx::cursor results = this->_db["users"].find(document{} << finalize);
	for (auto user : results) {
		json userData = json::parse(bsoncxx::to_json(user));
		players->push_back(LeaderboardEntry{userData["username"], userData["gameCount"], userData["wins"], (unsigned int)userData["gameCount"] - (unsigned int)userData["wins"]});
	}
	std::sort(players->begin(), players->end(), std::greater<LeaderboardEntry>());
	return *players;
}