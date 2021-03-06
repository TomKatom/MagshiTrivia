#pragma once
#include "ProtocolStructs.hpp"
#include "JsonResponsePacketSerializer.hpp"

class IRequestHandler
{
public:
	virtual bool isRequestValid(RequestInfo requestInfo) = 0;
	virtual RequestResult handleRequest(RequestInfo requestInfo) = 0;
};



