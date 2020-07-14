#include "RoomAdminRequestHandler.hpp"
#include "RequestHandlerFactory.hpp"


RoomAdminRequestHandler::RoomAdminRequestHandler(RequestHandlerFactory* factory, LoggedUser* user)  {
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
		this->_factory->getRoomManager().deleteRoom(this->m_loggedUser->getRoomId());
		delete this->_factory->getGameManager().findGame(this->m_loggedUser->getRoomId());
		response.status = ResponseStatus::closeRoomSuccess;
		requestRes.irequestHandler = this->_factory->createMenuRequestHandler(this->m_loggedUser);
	} catch (std::exception & e) {
		response.status = ResponseStatus::closeRoomError;
		requestRes.irequestHandler = this->_factory->createRoomAdminHandler(this->m_loggedUser);
	}
	requestRes.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	return requestRes;
}

RequestResult RoomAdminRequestHandler::startGame(RequestInfo requestInfo) {
	StartGameResponse response;
	RequestResult requestRes;
	try {
		this->_factory->getRoomManager().getRooms()[this->m_loggedUser->getRoomId()]->setActive(true);
		response.status = ResponseStatus::startGameSuccess;
		Room* currRoom = this->_factory->getRoomManager().getRooms()[this->m_loggedUser->getRoomId()];
		requestRes.irequestHandler = this->_factory->createGameRequestHandler(this->m_loggedUser, this->_factory->getGameManager().createGame(currRoom));
	}
	catch (std::exception & e) {
		response.status = ResponseStatus::startGameError;
		requestRes.irequestHandler = this->_factory->createMenuRequestHandler(this->m_loggedUser);
	}

	requestRes.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	return requestRes;
}

RequestResult RoomAdminRequestHandler::getRoomState(RequestInfo requestInfo) {
	GetRoomStateResponse response;
	RequestResult requestRes;

	try {
		Room room = *this->_factory->getRoomManager().getRooms()[this->m_loggedUser->getRoomId()];
		response.answerTimeout = room.getTimePerQuestion();
		response.hasGameBegun = room.getState();
		response.maxPlayers = room.getMaxPlayers();
		response.name = room.getName();
		response.id = room.getID();
		std::vector<std::string> players;
		for (auto& user : room.getAllUsers()) {
			players.push_back(user->getUsername());
		}
		if (response.hasGameBegun) {
			response.status = ResponseStatus::gameStarted;
		}
		else {
			response.status = ResponseStatus::getRoomStateSuccess;
		}
		response.players = players;
		response.questionCount = room.getQuestionsCount();
		requestRes.irequestHandler = this->_factory->createRoomAdminHandler(this->m_loggedUser);
	}
	catch (std::exception & e) {
		response.status = ResponseStatus::closeRoomError;
		requestRes.irequestHandler = this->_factory->createMenuRequestHandler(this->m_loggedUser);
	}

	requestRes.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	return requestRes;
}