#include "RoomMemberRequestHandler.hpp"
#include "RequestHandlerFactory.hpp"

RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory* factory, LoggedUser user) {
	this->_factory = factory;
	this->m_loggedUser = user;
}

bool RoomMemberRequestHandler::isRequestValid(RequestInfo requestInfo) {
	return (requestInfo.messageCode >= RequestCodes::getRoomStateRequest and requestInfo.messageCode <= RequestCodes::leaveRoomRequest);
}

RequestResult RoomMemberRequestHandler::handleRequest(RequestInfo requestInfo) {
	RequestResult requestRes;
	switch (requestInfo.messageCode)
	{
	case RequestCodes::getRoomStateRequest:
		requestRes = this->getRoomState(requestInfo);
		break;

	case RequestCodes::leaveRoomRequest:
		requestRes = this->leaveRoom(requestInfo);
		break;
	default:
		break;
	}

	return requestRes;
}

RequestResult RoomMemberRequestHandler::getRoomState(RequestInfo requestInfo) {
	GetRoomStateResponse response;
	RequestResult requestRes;

	try {
		Room room = this->_factory->getRoomManager().getRooms()[this->m_loggedUser.getRoomId()];
		response.answerTimeout = room.getTimePerQuestion();
		response.hasGameBegun = room.getState();
		response.maxPlayers = room.getMaxPlayers();
		response.name = room.getName();
		response.id = room.getID();
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

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo requestInfo) {
	LeaveRoomResponse response;
	RequestResult requestRes;

	try {
		this->_factory->getRoomManager().getRooms()[this->m_loggedUser.getRoomId()].removeUser(this->m_loggedUser);
		response.status = ResponseStatus::leaveRoomSuccess;
	}
	catch (std::exception & e) {
		response.status = ResponseStatus::leaveRoomError;
	}

	requestRes.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	return requestRes;
}
