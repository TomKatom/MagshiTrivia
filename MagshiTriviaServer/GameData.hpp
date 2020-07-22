#pragma once
#include "Question.hpp"
struct GameData {
	GameData() = default;
	GameData(Question* question, unsigned int correctCount, unsigned int wrongCount, unsigned int averageAnswerTime) { this->currentQuestion = question; this->correctQuestionCount = correctCount; this->wrongAnswerCount = wrongCount; this->averageAnswerTime = averageAnswerTime; }
	Question* currentQuestion;
	unsigned int correctQuestionCount;
	unsigned int wrongAnswerCount;
	long double averageAnswerTime;
};
