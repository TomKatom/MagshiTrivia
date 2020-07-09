#pragma once
#include "IRequestHandler.hpp"
	class RequestHandlerFactory;
#include "LoggedUser.hpp"


class RoomAdminRequestHandler :
	public IRequestHandler
{
public:
	RoomAdminRequestHandler(RequestHandlerFactory* factory, LoggedUser user);
	bool isRequestValid(RequestInfo requestInfo);
	RequestResult handleRequest(RequestInfo requestInfo);

private:
	LoggedUser m_loggedUser;
	RequestHandlerFactory* _factory;

	RequestResult closeRoom(RequestInfo requestInfo);
	RequestResult startGame(RequestInfo requestInfo);
	RequestResult getRoomState(RequestInfo requestInfo);
};

