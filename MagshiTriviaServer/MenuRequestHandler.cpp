#include "MenuRequestHandler.hpp"
#include "JsonRequestPacketDeserializer.hpp"
#include "RequestHandlerFactory.hpp"

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory* factory, LoggedUser user) {
	this->_factory = factory;
	this->m_loggedUser = user;
}

bool MenuRequestHandler::isRequestValid(RequestInfo requestInfo) {
	return (requestInfo.messageCode >= RequestCodes::createRoomRequest and requestInfo.messageCode <= RequestCodes::logoutRequest);
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo requestInfo) {
 	RequestResult result;
	switch (requestInfo.messageCode) {
		case RequestCodes::createRoomRequest:
			result = this->createRoom(requestInfo);
			break;
		case RequestCodes::getStatisticsRequest:
			result = this->getStatistics(requestInfo);
			break;
	}
	return result;
}

RequestResult MenuRequestHandler::signout(RequestInfo requestInfo) {
	LogoutResponse response;
	RequestResult requestRes;
	try {
		LogoutRequest logoutRequest = JsonRequestPacketDeserializer::deserializeLogoutRequest(requestInfo.buffer);
		this->_factory->getLoginManager().logout(logoutRequest.username);
		response.status = ResponseStatus::logoutSuccess;
		requestRes.irequestHandler = this->_factory->createLoginRequestHandler();
	}
	catch (std::exception & e) {
		response.status = ResponseStatus::logoutError;
		requestRes.irequestHandler = this->_factory->createLoginRequestHandler();
	}
	requestRes.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	return requestRes;
}

RequestResult MenuRequestHandler::getRooms(RequestInfo) {
	GetRoomsResponse response;
	RequestResult requestRes;
	try {
		response.rooms = this->_factory->getRoomManager().getRooms();
		response.status = ResponseStatus::getRoomsSuccess;
		requestRes.irequestHandler = this->_factory->createMenuRequestHandler(this->m_loggedUser);
	}
	catch (std::exception & e) {
		response.status = ResponseStatus::getRoomsError;
		requestRes.irequestHandler = this->_factory->createMenuRequestHandler(this->m_loggedUser);
	}
	requestRes.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	return requestRes;
}

RequestResult MenuRequestHandler::getStatistics(RequestInfo requestInfo) {
	
	RequestResult requestRes;
	UserStatistics response;
	
	try {
		response = this->_factory->getStatisticManager().getStatistics(this->m_loggedUser.getUsername());
		requestRes.buffer = JsonResponsePacketSerializer::serializeResponse(GetStatisticsResponse{0, response});
		requestRes.irequestHandler = this->_factory->createMenuRequestHandler(this->m_loggedUser);
	}
	catch (std::exception & e) {
		requestRes.irequestHandler = this->_factory->createMenuRequestHandler(this->m_loggedUser);
	}
	return requestRes;
}


RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo requestInfo) {
	GetPlayersInRoomResponse response;
	RequestResult requestRes;
	try {
		GetPlayersInRoomRequest getPlayersInRoomRequest = JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(requestInfo.buffer);

		response.players = this->_factory->getRoomManager().getPlayersInRoom(getPlayersInRoomRequest.roomId);
		requestRes.irequestHandler = this->_factory->createMenuRequestHandler(this->m_loggedUser);
	}
	catch (std::exception & e) {
		requestRes.irequestHandler = this->_factory->createMenuRequestHandler(this->m_loggedUser);
	}
	requestRes.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	return requestRes;
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo  requestInfo) {
	JoinRoomResponse response;
	RequestResult requestRes;
	try {
		JoinRoomRequest joinRoomRequest = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(requestInfo.buffer);
		response.status = ResponseStatus::joinRoomSuccess;
		//response.players = roomManager.join(getPlayersInRoomRequest.roomId);
		requestRes.irequestHandler = this->_factory->createMenuRequestHandler(this->m_loggedUser);
	}
	catch (std::exception & e) {
		response.status = ResponseStatus::joinRoomError;
		requestRes.irequestHandler = this->_factory->createMenuRequestHandler(this->m_loggedUser);
	}
	requestRes.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	return requestRes;
}

RequestResult MenuRequestHandler::createRoom(RequestInfo requestInfo) {
	CreateRoomResponse response;
	RequestResult requestRes;
	try {
		CreateRoomRequest createRoomRequest = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(requestInfo.buffer);
		RoomData roomData;
		roomData.name = createRoomRequest.roomName;
		roomData.maxPlayers = createRoomRequest.maxUsers;
		roomData.timePerQuestion = createRoomRequest.answerTimeout;
		roomData.questionsCount = createRoomRequest.questionCount;
		
	/*	{ createRoomRequest.roomName, createRoomRequest.maxUsers,
			createRoomRequest.answerTimeout, createRoomRequest.questionCount };*/

		this->_factory->getRoomManager().createRoom(roomData);
		response.status = ResponseStatus::createRoomSuccess;
		requestRes.irequestHandler = this->_factory->createMenuRequestHandler(this->m_loggedUser);
	}
	catch (std::exception & e) {
		response.status = ResponseStatus::createRoomError;
		requestRes.irequestHandler = this->_factory->createMenuRequestHandler(this->m_loggedUser);
	}
	requestRes.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	return requestRes;
}
