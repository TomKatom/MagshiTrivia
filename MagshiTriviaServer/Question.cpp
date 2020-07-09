#include "Question.hpp"

Question::Question(std::string question, std::string correctAnswer, std::list<std::string> wrongAnswers) {
	this->question = question;
	this->correctAnswer = correctAnswer;
	this->wrongAnswers = wrongAnswers;
}
std::string Question::getQuestion() {
	return this->question;
}
std::string Question::getCorrectAnswer() {
	return this->correctAnswer;
}
std::list<std::string> Question::getWrongAnswers() {
	return this->wrongAnswers;
}