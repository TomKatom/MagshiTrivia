#pragma once
#include "IRequestHandler.hpp"
class RequestHandlerFactory;

class LoginRequestHandler : public IRequestHandler
{
public:
	LoginRequestHandler(RequestHandlerFactory* factory);
	bool isRequestValid(RequestInfo requestInfo) ;
	RequestResult handleRequest(RequestInfo requestInfo);

private:
	RequestHandlerFactory* _factory;
	RequestResult login(RequestInfo requestInfo);
	RequestResult signup(RequestInfo requestInfo);

};

