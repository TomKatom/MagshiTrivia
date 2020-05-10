#pragma once
#include "ProtocolStructs.hpp"

class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(std::vector<unsigned char> buffer);
	static SignupRequest deserializeSignUpRequest(std::vector<unsigned char> buffer);
	static RequestInfo getRequestInfo(std::vector< unsigned char > buffer);

};

