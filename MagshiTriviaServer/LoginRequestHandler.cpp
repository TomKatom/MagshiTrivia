#include "LoginRequestHandler.hpp"
#include <iostream>
#include "LoginManager.hpp"
#include "JsonRequestPacketDeserializer.hpp"
#include "RequestHandlerFactory.hpp"

bool LoginRequestHandler::isRequestValid(RequestInfo requestInfo) {
	return(requestInfo.messageCode == RequestCodes::loginRequestCode or requestInfo.messageCode == RequestCodes::signupRequestCode);
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo requestInfo) {
	RequestResult requestRes;
	if (requestInfo.messageCode == RequestCodes::loginRequestCode) {
		requestRes =  login(requestInfo);
	}
	else {
		requestRes = signup(requestInfo);
	}

	return requestRes;

}

RequestResult LoginRequestHandler::login(RequestInfo requestInfo) {
	RequestHandlerFactory handlerFactory;
	LoginManager loginManager;
	RequestResult requestRes;
	LoginResponse response;
	try {
		LoginRequest request = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo.buffer);
		loginManager.login(request.userName, request.password);
		response.status = ResponseStatus::loginSuccess;
		requestRes.irequestHandler = handlerFactory.createMenuRequestHandler();
	}
	catch (std::exception & e) {
		response.status = ResponseStatus::loginError;
		requestRes.irequestHandler = handlerFactory.createLoginRequestHandler();
	}
	requestRes.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	return requestRes;
}

RequestResult LoginRequestHandler::signup(RequestInfo requestInfo) {
	SignupResponse response;
	RequestHandlerFactory handlerFactory;
	LoginManager loginManager;
	RequestResult requestRes;
	try {
		SignupRequest request = JsonRequestPacketDeserializer::deserializeSignUpRequest(requestInfo.buffer);
		loginManager.signup(request.username, request.password, request.email);
		response.status = ResponseStatus::signUpSuccess;
		requestRes.irequestHandler = handlerFactory.createLoginRequestHandler();
	}
	catch (std::exception & e) {
		response.status = ResponseStatus::signUpError;
		requestRes.irequestHandler = handlerFactory.createLoginRequestHandler();
	}
	requestRes.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	return requestRes;
}