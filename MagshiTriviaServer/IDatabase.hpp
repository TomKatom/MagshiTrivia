#pragma once
#include <string>
#include <vector>
#include "Question.hpp"

class IDatabase {
public:
	virtual ~IDatabase() = default;
	virtual bool doesUserExist(std::string username) = 0;
	virtual bool doesPasswordMatch(std::string username, std::string password) = 0;
	virtual void addNewUser(std::string username, std::string password, std::string email) = 0;

	virtual std::vector<Question> getQuestions(int x) = 0;
	virtual float getAverageAnswerTime(std::string name) = 0;
	virtual int getNumOfCorrectAnswers(std::string name) = 0;
	virtual int getNumOfTotalAnswers(std::string name) = 0;
	virtual int getNumOfPlayerGames(std::string name) = 0;
};