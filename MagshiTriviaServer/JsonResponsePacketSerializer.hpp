#pragma once
#include "ProtocolStructs.hpp"
#include <vector>

class JsonResponsePacketSerializer
{
public:

	static std::vector<unsigned char> serializeResponse(ErrorResponse);
	static std::vector<unsigned char> serializeResponse(LoginResponse);
	static std::vector<unsigned char>  serializeResponse(SignupResponse);
private:

};

