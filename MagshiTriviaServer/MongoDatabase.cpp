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
#include "nlohmann/json.hpp"

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
		<< "averageTimeForAnswer" << 0
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


std::list<Question> MongoDatabase::getQuestions(int x)
{
	mongocxx::collection questions = this->_db["questions"];
	mongocxx::cursor result = questions.find(document{} << "$sample" << document{} << "size" << x << finalize);
	std::list<Question> questionList;
	return questionList;
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