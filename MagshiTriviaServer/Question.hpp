#pragma once
#include <string>
#include <vector>

class Question {
public:
	Question() = default;
	Question(std::string question, std::string correctAnswer, std::vector<std::string> possibleAnswers);
	std::string getQuestion();
	std::string getCorrectAnswer();
	std::vector<std::string> getPossibleAnswers();
private:
	std::string question;
	std::string correctAnswer;
	std::vector<std::string> possibleAnswers;
};