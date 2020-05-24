#pragma once
#include "IRequestHandler.hpp"

class MenuRequestHandler : public IRequestHandler
{
public:
	bool isRequestValid(RequestInfo requestInfo);
	RequestResult handleRequest(RequestInfo requestInfo);

private:

};
