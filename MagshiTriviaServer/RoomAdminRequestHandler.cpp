#include "RoomAdminRequestHandler.hpp"
#include "RequestHandlerFactory.hpp"


RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory* factory, LoggedUser user) {
	this->_factory = factory;
	this->m_loggedUser = user;
}

bool RoomAdminRequestHandler::isRequestValid(RequestInfo requestInfo) {
	return (requestInfo.messageCode >= RequestCodes::closeRoomRequest and requestInfo.messageCode <= RequestCodes::leaveRoomRequest);
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo requestInfo) {
	RequestResult requestRes;
	switch (requestInfo.messageCode)
	{
	case RequestCodes::closeRoomRequest:
		requestRes = this->closeRoom(requestInfo);
		break;

	default:
		break;
	}

	return requestRes;
}

RequestResult RoomAdminRequestHandler::closeRoom(RequestInfo requestInfo) {
	CloseRoomResponse response;
	RequestResult requestRes;

	try {
		this->_factory.

	} catch (std::exception & e) {
		response.status = ResponseStatus::logoutError;
		//requestRes.irequestHandler = this->_factory->
	}

}