#include "LoginRequestHandler.hpp"
#include <iostream>
#include "JsonRequestPacketDeserializer.hpp"
#include "RequestHandlerFactory.hpp"

LoginRequestHandler::LoginRequestHandler(RequestHandlerFactory* factory) {
	this->_factory = factory;
}

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
	RequestResult requestRes;
	LoginResponse response;
	try {
		LoginRequest request = JsonRequestPacketDeserializer::deserializeLoginRequest(requestInfo.buffer);
		LoggedUser* user = this->_factory->getLoginManager().login(request.userName, request.password);
		response.status = ResponseStatus::loginSuccess;
		requestRes.irequestHandler = this->_factory->createMenuRequestHandler(*user);
	}
	catch (std::exception & e) {
		response.status = ResponseStatus::loginError;
		requestRes.irequestHandler = this->_factory->createLoginRequestHandler();
	}
	requestRes.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	return requestRes;
}

RequestResult LoginRequestHandler::signup(RequestInfo requestInfo) {
	SignupResponse response;
	RequestResult requestRes;
	try {
		SignupRequest request = JsonRequestPacketDeserializer::deserializeSignUpRequest(requestInfo.buffer);
		this->_factory->getLoginManager().signup(request.username, request.password, request.email);
		response.status = ResponseStatus::signUpSuccess;
		requestRes.irequestHandler = this->_factory->createLoginRequestHandler();
	}
	catch (std::exception & e) {
		response.status = ResponseStatus::signUpError;
		requestRes.irequestHandler = this->_factory->createLoginRequestHandler();
	}
	requestRes.buffer = JsonResponsePacketSerializer::serializeResponse(response);
	return requestRes;
}