#include "Question.hpp"

Question::Question(std::string question, std::string correctAnswer, std::vector<std::string> possibleAnswers) {
	this->question = question;
	this->correctAnswer = correctAnswer;
	this->possibleAnswers = possibleAnswers;
}
std::string Question::getQuestion() {
	return this->question;
}
std::string Question::getCorrectAnswer() {
	return this->correctAnswer;
}
std::vector<std::string> Question::getPossibleAnswers() {
	return this->possibleAnswers;
}