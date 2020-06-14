#pragma once
#include "ProtocolStructs.hpp"
#include <vector>

class JsonResponsePacketSerializer
{
public:

	//V1
	static std::vector<unsigned char> serializeResponse(ErrorResponse);
	static std::vector<unsigned char> serializeResponse(LoginResponse);
	static std::vector<unsigned char>  serializeResponse(SignupResponse);

	//V2
	static std::vector<unsigned char>  serializeResponse(LogoutResponse);
	static std::vector<unsigned char>  serializeResponse(GetRoomsResponse);
	static std::vector<unsigned char> serializeResponse(GetPlayersInRoomResponse); 
	static std::vector<unsigned char> serializeResponse(JoinRoomResponse); 
	static std::vector<unsigned char> serializeResponse(CreateRoomResponse);
	static std::vector<unsigned char> serializeResponse(GetStatisticsResponse);


private:
	static void insertInt2Vector(std::vector<unsigned char>& vector, int val);
};

