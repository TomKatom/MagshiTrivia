#pragma once
#include "ProtocolStructs.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class JsonRequestPacketDeserializer
{
public:
	static LoginRequest deserializeLoginRequest(std::vector<unsigned char> buffer);
	static SignupRequest deserializeSignUpRequest(std::vector<unsigned char> buffer);
	static RequestInfo getRequestInfo(std::vector< unsigned char > buffer);

	//V2
	static LogoutRequest deserializeLogoutRequest(std::vector<unsigned char> buffer);
	static GetPlayersInRoomRequest deserializeGetPlayersInRoomRequest(std::vector< unsigned char > buffer);
	static JoinRoomRequest deserializeJoinRoomRequest(std::vector< unsigned char > buffer);
	static CreateRoomRequest deserializeCreateRoomRequest(std::vector< unsigned char > buffer);

	//V3



private:
	static json getJsonFromBuffer(std::vector< unsigned char > buffer);
};

