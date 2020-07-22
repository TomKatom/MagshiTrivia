#include "RoomMemberRequestHandler.hpp"
#include "RequestHandlerFactory.hpp"

RoomMemberRequestHandler::RoomMemberRequestHandler(RequestHandlerFactory* factory, LoggedUser* user) {  
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

	if (this->_factory->getRoomManager().getRooms().find(this->m_loggedUser->getRoomId()) != this->_factory->getRoomManager().getRooms().end()) {
		try {
			Room room = *this->_factory->getRoomManager().getRooms()[this->m_loggedUser->getRoomId()];
			response.answerTimeout = room.getTimePerQuestion();
			response.hasGameBegun = room.getState();
			response.maxPlayers = room.getMaxPlayers();
			response.name = room.getName();
			response.id = room.getID();
			response.questionCount = room.getQuestionsCount();
			std::vector<std::string> players;
			for (auto& user : room.getAllUsers()) {
				players.push_back(user->getUsername());
			}
			if (response.hasGameBegun) {
				response.status = ResponseStatus::gameStarted;
				this->_factory->getRoomManager().getRooms()[this->m_loggedUser->getRoomId()]->setActive(true);
				Room currRoom = *this->_factory->getRoomManager().getRooms()[this->m_loggedUser->getRoomId()];
				requestRes.irequestHandler = this->_factory->createGameRequestHandler(this->m_loggedUser, this->_factory->getGameManager().findGame(this->m_loggedUser->getRoomId()));
			}
			else {
				response.status = ResponseStatus::getRoomStateSuccess;
				response.players = players;
				response.questionCount = room.getQuestionsCount();
				requestRes.irequestHandler = this->_factory->createRoomMemberHandler(this->m_loggedUser);
			}
		}
		catch (std::exception & e) {
			response.status = ResponseStatus::getRoomStateError;
			requestRes.irequestHandler = this->_factory->createMenuRequestHandler(this->m_loggedUser);
		}
	}
	else {
		response.status = ResponseStatus::roomClosed;
		response.answerTimeout = 0;
		response.hasGameBegun = false;
		response.questionCount = 0;
		response.maxPlayers = 0;
		response.name = "";
		response.id = 0;
		response.players = std::vector<std::string>();
		this->m_loggedUser->setRoomId(-1);
		requestRes.irequestHandler = this->_factory->createMenuRequestHandler(this->m_loggedUser);
	}
	requestRes.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	return requestRes;
}

RequestResult RoomMemberRequestHandler::leaveRoom(RequestInfo requestInfo) {
	LeaveRoomResponse response;
	RequestResult requestRes;

	try {
		this->_factory->getRoomManager().getRooms()[this->m_loggedUser->getRoomId()]->removeUser(this->m_loggedUser);
		response.status = ResponseStatus::leaveRoomSuccess;
		this->m_loggedUser->setRoomId(-1);
		requestRes.irequestHandler = this->_factory->createMenuRequestHandler(this->m_loggedUser);
	}
	catch (std::exception & e) {
		response.status = ResponseStatus::leaveRoomError;
	}

	requestRes.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	requestRes.irequestHandler = this->_factory->createMenuRequestHandler(this->m_loggedUser);
	return requestRes;
}

