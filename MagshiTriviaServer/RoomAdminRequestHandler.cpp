#include "RoomAdminRequestHandler.hpp"
#include "RequestHandlerFactory.hpp"


RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory* factory, LoggedUser user) {
	this->_factory = factory;
	this->m_loggedUser = user;
}

bool RoomAdminRequestHandler::isRequestValid(RequestInfo requestInfo) {
	return (requestInfo.messageCode >= RequestCodes::closeRoomRequest and requestInfo.messageCode <= RequestCodes::getRoomStateRequest);
}

RequestResult RoomAdminRequestHandler::handleRequest(RequestInfo requestInfo) {
	RequestResult requestRes;
	switch (requestInfo.messageCode)
	{
	case RequestCodes::closeRoomRequest:
		requestRes = this->closeRoom(requestInfo);
		break;

	case RequestCodes::startGameRequest:
		requestRes = this->startGame(requestInfo);
		break;
	case RequestCodes::getRoomStateRequest:
		requestRes = this->getRoomState(requestInfo);
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
		this->_factory->getRoomManager().deleteRoom(this->m_loggedUser.getRoomId());
		response.status = ResponseStatus::closeRoomSuccess;
	} catch (std::exception & e) {
		response.status = ResponseStatus::closeRoomError;
	}

	requestRes.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	return requestRes;
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo requestInfo) {
	StartGameResponse response;
	RequestResult requestRes;

	try {
		//this->_factory->getRoomManager().
		response.status = ResponseStatus::closeRoomSuccess;
	}
	catch (std::exception & e) {
		response.status = ResponseStatus::closeRoomError;
	}

	requestRes.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	return requestRes;
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo requestInfo) {
	GetRoomStateResponse response;
	RequestResult requestRes;

	try {
		Room room = this->_factory->getRoomManager().getRooms()[this->m_loggedUser.getRoomId()];
		response.answerTimeout = room.getTimePerQuestion();
		response.hasGameBegun = room.getState();
		std::vector<std::string> players;
		for (auto& user : room.getAllUsers()) {
			players.push_back(user.getUsername());
		}
		response.players = players;
		response.questionCount = room.getQuestionsCount();
	}
	catch (std::exception & e) {
		response.status = ResponseStatus::closeRoomError;
	}

	requestRes.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	return requestRes;
}