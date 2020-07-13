#include "GameRequestHandler.hpp"
#include "RequestHandlerFactory.hpp"
#include "JsonRequestPacketDeserializer.hpp"
#include <algorithm>

GameRequestHandler::GameRequestHandler(RequestHandlerFactory* m_factory, LoggedUser* user, Game* game)  {
	this->m_factory = m_factory;
	this->m_user = user;
	this->m_game = game;
}

bool GameRequestHandler::isRequestValid(RequestInfo requestInfo)
{
	return (requestInfo.messageCode >= RequestCodes::leaveGameRequest and requestInfo.messageCode <= RequestCodes::getGameResultRequest);
}

RequestResult GameRequestHandler::handleRequest(RequestInfo requestInfo)
{
	RequestResult requestRes;
	switch (requestInfo.messageCode) {
	case RequestCodes::leaveGameRequest:
		requestRes = leaveGame(requestInfo);
		break;
	case RequestCodes::getQuestionRequest:
		requestRes = getQuestion(requestInfo);
		break;
	case RequestCodes::getGameResultRequest:
		requestRes = getGameResults(requestInfo);
		break;
	case RequestCodes::submitAnswerRequest:
		requestRes = submitAnswer(requestInfo);
		break;
	}
	return requestRes;
}

RequestResult GameRequestHandler::leaveGame(RequestInfo requestInfo) {
	RequestResult requestRes;
	LeaveGameResponse res;
	try {
		this->m_game->getPlayers()[this->m_user]->wrongAnswerCount = this->m_game->getQuestions().size() - this->m_game->getPlayers()[this->m_user]->correctQuestionCount;
		this->m_game->getPlayers()[this->m_user]->averageAnswerTime = 100;
		this->m_factory->getRoomManager().getRooms()[this->m_user->getRoomId()]->removeUser(this->m_user);
		res.status = ResponseStatus::leaveGameSuccess;
		requestRes.irequestHandler = this->m_factory->createMenuRequestHandler(this->m_user);
	}
	catch (const std::exception& e) {
		res.status = ResponseStatus::leaveGameError;
		requestRes.irequestHandler = this->m_factory->createGameRequestHandler(this->m_user, this->m_game);
	}
	requestRes.buffer = JsonResponsePacketSerializer::serializeResponse(res);
	return requestRes;
}

RequestResult GameRequestHandler::getQuestion(RequestInfo requestInfo) {
	RequestResult requestRes;
	GetQuestionResponse res;
	try {
		res.question = this->m_game->getQuestionForUser(this->m_user).getQuestion();
		res.answers = this->m_game->getQuestionForUser(this->m_user).getPossibleAnswers();
		res.status = ResponseStatus::getQuestionSuccess;
		if (this->m_game->getPlayers()[this->m_user]->wrongAnswerCount + this->m_game->getPlayers()[this->m_user]->correctQuestionCount == 0) { // if this is the first get question
			this->m_game->getPlayers()[this->m_user]->averageAnswerTime = requestInfo.receivalTime; // when it gets here it inititates the time value
		}
		requestRes.irequestHandler = this->m_factory->createGameRequestHandler(this->m_user, this->m_game);
	}
	catch (const std::exception& e) {
		res.status = ResponseStatus::getQuestionError;
		requestRes.irequestHandler = this->m_factory->createGameRequestHandler(this->m_user, this->m_game);
	}
	requestRes.buffer = JsonResponsePacketSerializer::serializeResponse(res);
	return requestRes;
}

RequestResult GameRequestHandler::getGameResults(RequestInfo requestInfo) {
	RequestResult requestRes;
	GetGameResultsResponse res;
	std::vector<PlayerResults> results;
	try {
		if (!this->m_game->isFinished()) {
			res.status = ResponseStatus::gameHasNotEnded;
			requestRes.irequestHandler = this->m_factory->createGameRequestHandler(this->m_user, this->m_game);
		}
		else {
			res.results = this->m_game->getResults();
			res.status = ResponseStatus::getGameResultSuccess;
			requestRes.irequestHandler = this->m_factory->createMenuRequestHandler(this->m_user);
		}
	}
	catch (const std::exception& e) {
		res.status = ResponseStatus::getGameResultError;
		requestRes.irequestHandler = this->m_factory->createGameRequestHandler(this->m_user, this->m_game);
	}
	requestRes.buffer = JsonResponsePacketSerializer::serializeResponse(res);
	return requestRes;
}

RequestResult GameRequestHandler::submitAnswer(RequestInfo requestInfo) {
	RequestResult requestRes;
	SubmitAnswerResponse res;
	SubmitAnswerRequest request = JsonRequestPacketDeserializer::deserializeSubmitAnswerRequest(requestInfo.buffer);
	int i = 0;
	try {
		this->m_game->SubmitAnswer(requestInfo, this->m_user, request.answerId);
		std::string correctAnswer = this->m_game->getQuestionForUser(this->m_user).getCorrectAnswer();
		for (auto answer : this->m_game->getQuestionForUser(this->m_user).getPossibleAnswers()) {
			i++;
			if (answer == correctAnswer) {
				break;
			}
		}
		if (this->m_game->getPlayers()[this->m_user]->wrongAnswerCount + this->m_game->getPlayers()[this->m_user]->correctQuestionCount == this->m_game->getQuestions().size()) { // if this is the last submit answer
			this->m_game->getPlayers()[this->m_user]->averageAnswerTime = requestInfo.receivalTime - this->m_game->getPlayers()[this->m_user]->averageAnswerTime;
			this->m_game->getPlayers()[this->m_user]->averageAnswerTime /= (long double)this->m_game->getQuestions().size();
		}
		this->m_game->setFinished(true);
		for (auto player : this->m_game->getPlayers()) {
			if (player.second->correctQuestionCount + player.second->wrongAnswerCount != this->m_game->getQuestions().size()) {
				this->m_game->setFinished(false);
				break;
			}
		}
		if (this->m_game->isFinished()) {
			this->m_game->generateResults();
			this->m_factory->getStatisticManager().updateStatistics(this->m_game->getResults()[0], true);
			for (int i = 1; i < this->m_game->getResults().size(); i++) {
					this->m_factory->getStatisticManager().updateStatistics(this->m_game->getResults()[i], false);
			}
			this->m_game->getPlayers().clear();
			this->m_factory->getRoomManager().deleteRoom(this->m_user->getRoomId());
		}
		res.correctAnswerId = i;
		res.status = ResponseStatus::submitAnswerSuccess;
		requestRes.irequestHandler = this->m_factory->createGameRequestHandler(this->m_user, this->m_game);
	}
	catch (const std::exception& e) {
		res.status = ResponseStatus::submitAnswerError;
		requestRes.irequestHandler = this->m_factory->createGameRequestHandler(this->m_user, this->m_game);
	}
	requestRes.buffer = JsonResponsePacketSerializer::serializeResponse(res);
	return requestRes;
}

