#pragma once
#include "IRequestHandler.hpp"
class RequestHandlerFactory;
#include "LoggedUser.hpp"


class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(RequestHandlerFactory* factory, LoggedUser* user);
	bool isRequestValid(RequestInfo requestInfo);
	RequestResult handleRequest(RequestInfo requestInfo);

private:
	LoggedUser* m_loggedUser;
	RequestHandlerFactory* _factory;
	RequestResult signout(RequestInfo);
	RequestResult getRooms(RequestInfo);
	RequestResult getPlayersInRoom(RequestInfo);
	RequestResult getStatistics(RequestInfo);
	RequestResult getLeaderboard(RequestInfo);
	RequestResult joinRoom(RequestInfo);
	RequestResult createRoom(RequestInfo);
};
