#pragma once
#include "IRequestHandler.hpp"
#include "Game.hpp"
#include "LoggedUser.hpp"

class RequestHandlerFactory;

class GameRequestHandler : public IRequestHandler {

private:
	Game m_game;
	LoggedUser m_user;
	RequestHandlerFactory* m_factory;
	RequestResult getQuestion(RequestInfo request);
	RequestResult submitAnswer(RequestInfo request);
	RequestResult getGameResults(RequestInfo request);
	RequestResult leaveGame(RequestInfo request);
public:
	GameRequestHandler(RequestHandlerFactory* m_factory, LoggedUser m_user, Game m_game);
	virtual bool isRequestValid(RequestInfo requestInfo) override;
	virtual RequestResult handleRequest(RequestInfo requestInfo) override;

};