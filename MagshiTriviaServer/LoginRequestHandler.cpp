#include "LoginRequestHandler.hpp"
#include <iostream>
bool LoginRequestHandler::isRequestValid(RequestInfo requestInfo) {
	return(requestInfo.messageCode == RequestCodes::loginRequestCode or requestInfo.messageCode == RequestCodes::signupRequestCode);
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo requestInfo) {
	RequestResult a;
	if (requestInfo.messageCode == RequestCodes::loginRequestCode) {
		//calls relevent idatbase function
		//a = login(requestInfo);
	}
	else {
		//a = signup(requestInfo);
	}

	//test
	LoginResponse l;
	l.status = 1;
	a.buffer = JsonResponsePacketSerializer::serializeResponse(l);
	a.irequestHandler = nullptr;
	//test


	return a;

}
