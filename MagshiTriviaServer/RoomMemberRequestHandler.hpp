#pragma once
#include "IRequestHandler.hpp"
class RequestHandlerFactory;
#include "LoggedUser.hpp"

class RoomMemberRequestHandler :
	public IRequestHandler
{
public:
	RoomMemberRequestHandler(RequestHandlerFactory* factory, LoggedUser user);
	bool isRequestValid(RequestInfo requestInfo);
	RequestResult handleRequest(RequestInfo requestInfo);

private:
	LoggedUser m_loggedUser;
	RequestHandlerFactory* _factory;

	RequestResult getRoomState(RequestInfo requestInfo);	
	RequestResult leaveRoom(RequestInfo requestInfo);

};

