#include "LoginRequestHandler.hpp"

bool LoginRequestHandler::isRequestValid(RequestInfo requestInfo) {
	return(requestInfo.messageCode == RequestCodes::loginRequestCode or requestInfo.messageCode == RequestCodes::signupRequestCode);
}

RequestResult LoginRequestHandler::handleRequest(RequestInfo requestInfo) {
	RequestResult a;
	if (requestInfo.messageCode == ResponseCodes::loginResponseCode) {

	}
	else {

	}
	return a;
}
