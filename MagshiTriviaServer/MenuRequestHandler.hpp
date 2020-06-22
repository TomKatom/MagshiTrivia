#pragma once
#include "IRequestHandler.hpp"
class RequestHandlerFactory;
#include "LoggedUser.hpp"


class MenuRequestHandler : public IRequestHandler
{
public:
	MenuRequestHandler(RequestHandlerFactory* factory);
	bool isRequestValid(RequestInfo requestInfo);
	RequestResult handleRequest(RequestInfo requestInfo);

private:
	RequestHandlerFactory* _factory;
	RequestResult signout(RequestInfo);
	RequestResult getRooms(RequestInfo);
	RequestResult getPlayersInRoom(RequestInfo);
	RequestResult getStatistics(RequestInfo);
	RequestResult joinRoom(RequestInfo);
	RequestResult createRoom(RequestInfo);
};
