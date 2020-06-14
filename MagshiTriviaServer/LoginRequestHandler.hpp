#pragma once
#include "IRequestHandler.hpp"

class LoginRequestHandler : public IRequestHandler
{
public:
	bool isRequestValid(RequestInfo requestInfo) ;
	RequestResult handleRequest(RequestInfo requestInfo);

private:
	RequestResult login(RequestInfo requestInfo);
	RequestResult signup(RequestInfo requestInfo);

};

