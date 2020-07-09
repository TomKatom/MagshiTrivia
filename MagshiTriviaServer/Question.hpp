#include <string>
#include <list>

class Question {
public:
	Question(std::string question, std::string correctAnswer, std::list<std::string> correctAnswers);
	std::string getQuestion();
	std::string getCorrectAnswer();
	std::list<std::string> getWrongAnswers();
private:
	std::string question;
	std::string correctAnswer;
	std::list<std::string> wrongAnswers;
};