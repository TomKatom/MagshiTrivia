#include "MenuRequestHandler.hpp"
#include "JsonRequestPacketDeserializer.hpp"
#include "RequestHandlerFactory.hpp"

MenuRequestHandler::MenuRequestHandler(RequestHandlerFactory* factory) {
	this->_factory = factory;
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
		requestRes.irequestHandler = this->_factory->createMenuRequestHandler();
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
		requestRes.irequestHandler = this->_factory->createMenuRequestHandler();
	}
	catch (std::exception & e) {
		response.status = ResponseStatus::getRoomsError;
		requestRes.irequestHandler = this->_factory->createMenuRequestHandler();
	}
	requestRes.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	return requestRes;
}

RequestResult MenuRequestHandler::getStatistics(RequestInfo) {
	
	return RequestResult{};
}


RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo requestInfo) {
	GetPlayersInRoomResponse response;
	RequestResult requestRes;
	try {
		GetPlayersInRoomRequest getPlayersInRoomRequest = JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(requestInfo.buffer);

		response.players = this->_factory->getRoomManager().getPlayersInRoom(getPlayersInRoomRequest.roomId);
		requestRes.irequestHandler = this->_factory->createMenuRequestHandler();
	}
	catch (std::exception & e) {
		requestRes.irequestHandler = this->_factory->createMenuRequestHandler();
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
		requestRes.irequestHandler = this->_factory->createMenuRequestHandler();
	}
	catch (std::exception & e) {
		response.status = ResponseStatus::joinRoomError;
		requestRes.irequestHandler = this->_factory->createMenuRequestHandler();
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
		requestRes.irequestHandler = this->_factory->createMenuRequestHandler();
	}
	catch (std::exception & e) {
		response.status = ResponseStatus::createRoomError;
		requestRes.irequestHandler = this->_factory->createMenuRequestHandler();
	}
	requestRes.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	return requestRes;
}
