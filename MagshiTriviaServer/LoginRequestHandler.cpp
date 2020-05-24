#include "LoginRequestHandler.hpp"
#include <iostream>
#include "LoginManager.hpp"
#include "JsonRequestPacketDeserializer.hpp"
#include "RequestHandlerFactory.hpp"

bool LoginRequestHandler::isRequestValid(RequestInfo requestInfo) {
	return(requestInfo.messageCode == RequestCodes::loginRequestCode or requestInfo.messageCode == RequestCodes::signupRequestCode);
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo requestInfo) {
	RequestHandlerFactory handlerFactory;
	LoginManager loginManager;
	RequestResult a;
	if (requestInfo.messageCode == RequestCodes::loginRequestCode) {
		LoginResponse response;
		try {
			LoginRequest request = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo.buffer);
			loginManager.login(request.userName, request.password);
			response.status = ResponseStatus::loginSuccess;
			a.irequestHandler = handlerFactory.createMenuRequestHandler();
		}
		catch (std::exception & e) {
			response.status = ResponseStatus::loginError;
			a.irequestHandler = handlerFactory.createLoginRequestHandler();
		}
		a.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	}
	else {
		SignupResponse response;
		try {
			SignupRequest request = JsonRequestPacketDeserializer::deserializeSignUpRequest(requestInfo.buffer);
			loginManager.signup(request.username, request.password, request.email);
			response.status = ResponseStatus::SignUpSuccess;
			a.irequestHandler = handlerFactory.createLoginRequestHandler();
		}
		catch (std::exception & e) {
			response.status = ResponseStatus::SignUpError;
			a.irequestHandler = handlerFactory.createLoginRequestHandler();
		}
		a.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	}

	return a;

}
