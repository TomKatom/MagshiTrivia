#include "MenuRequestHandler.hpp"
#include "JsonRequestPacketDeserializer.hpp"
#include "LoginManager.hpp"
#include "RequestHandlerFactory.hpp"
#include "RoomManager.hpp"
#include "RoomData.hpp"

bool MenuRequestHandler::isRequestValid(RequestInfo requestInfo) {
	return (requestInfo.messageCode >= RequestCodes::createRoomRequest and requestInfo.messageCode <= RequestCodes::logoutRequest);
}

RequestResult MenuRequestHandler::handleRequest(RequestInfo requestInfo) {
	switch (requestInfo.messageCode) {
	case RequestCodes::createRoomRequest:
		
		break;
	}
	return RequestResult{};
}

RequestResult MenuRequestHandler::signout(RequestInfo requestInfo) {
	LoginManager loginManager;
	LogoutResponse response;
	RequestResult requestRes;
	RequestHandlerFactory handlerFactory;

	try {
		LogoutRequest logoutRequest = JsonRequestPacketDeserializer::deserializeLogoutRequest(requestInfo.buffer);
		loginManager.logout(logoutRequest.username);
		response.status = ResponseStatus::logoutSuccess;
		requestRes.irequestHandler = handlerFactory.createMenuRequestHandler();
	}
	catch (std::exception & e) {
		response.status = ResponseStatus::logoutError;
		requestRes.irequestHandler = handlerFactory.createLoginRequestHandler();
	}
	requestRes.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	return requestRes;
}

RequestResult MenuRequestHandler::getRooms(RequestInfo) {
	RoomManager roomManager;
	GetRoomsResponse response;
	RequestResult requestRes;
	RequestHandlerFactory handlerFactory;

	try {
		response.rooms = roomManager.getRooms();
		response.status = ResponseStatus::getRoomsSuccess;
		requestRes.irequestHandler = handlerFactory.createMenuRequestHandler();
	}
	catch (std::exception & e) {
		response.status = ResponseStatus::getRoomsError;
		requestRes.irequestHandler = handlerFactory.createMenuRequestHandler();
	}
	requestRes.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	return requestRes;
}

RequestResult MenuRequestHandler::getStatistics(RequestInfo) {
	
	return RequestResult{};
}


RequestResult MenuRequestHandler::getPlayersInRoom(RequestInfo requestInfo) {
	RoomManager roomManager;
	GetPlayersInRoomResponse response;
	RequestResult requestRes;
	RequestHandlerFactory handlerFactory;

	try {
		GetPlayersInRoomRequest getPlayersInRoomRequest = JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(requestInfo.buffer);

		response.players= roomManager.getPlayersInRoom(getPlayersInRoomRequest.roomId);
		requestRes.irequestHandler = handlerFactory.createMenuRequestHandler();
	}
	catch (std::exception & e) {
		requestRes.irequestHandler = handlerFactory.createMenuRequestHandler();
	}
	requestRes.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	return requestRes;
}

RequestResult MenuRequestHandler::joinRoom(RequestInfo  requestInfo) {
	RoomManager roomManager;
	JoinRoomResponse response;
	RequestResult requestRes;
	RequestHandlerFactory handlerFactory;

	try {
		JoinRoomRequest joinRoomRequest = JsonRequestPacketDeserializer::deserializeJoinRoomRequest(requestInfo.buffer);
		response.status = ResponseStatus::joinRoomSuccess;
		//response.players = roomManager.join(getPlayersInRoomRequest.roomId);
		requestRes.irequestHandler = handlerFactory.createMenuRequestHandler();
	}
	catch (std::exception & e) {
		response.status = ResponseStatus::joinRoomError;
		requestRes.irequestHandler = handlerFactory.createMenuRequestHandler();
	}
	requestRes.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	return requestRes;
}

RequestResult MenuRequestHandler::createRoom(RequestInfo requestInfo) {
	RoomManager roomManager;
	CreateRoomResponse response;
	RequestResult requestRes;
	RequestHandlerFactory handlerFactory;

	try {
		CreateRoomRequest createRoomRequest = JsonRequestPacketDeserializer::deserializeCreateRoomRequest(requestInfo.buffer);
		RoomData roomData;
		roomData.name = createRoomRequest.roomName;
		roomData.maxPlayers = createRoomRequest.maxUsers;
		roomData.timePerQuestion = createRoomRequest.answerTimeout;
		roomData.questionsCount = createRoomRequest.questionCount;
		
	/*	{ createRoomRequest.roomName, createRoomRequest.maxUsers,
			createRoomRequest.answerTimeout, createRoomRequest.questionCount };*/

		roomManager.createRoom(roomData);
		response.status = ResponseStatus::createRoomSuccess;
		requestRes.irequestHandler = handlerFactory.createMenuRequestHandler();
	}
	catch (std::exception & e) {
		response.status = ResponseStatus::createRoomError;
		requestRes.irequestHandler = handlerFactory.createMenuRequestHandler();
	}
	requestRes.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	return requestRes;
}
