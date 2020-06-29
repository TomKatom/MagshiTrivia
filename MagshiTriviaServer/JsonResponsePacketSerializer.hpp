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

	//V3
	static std::vector<unsigned char>  serializeResponse(CloseRoomResponse);
	static std::vector<unsigned char>  serializeResponse(StartGameResponse);
	static std::vector<unsigned char>  serializeResponse(GetRoomStateResponse);
	static std::vector<unsigned char>  serializeResponse(LeaveRoomResponse);


private:
	static void insertInt2Vector(std::vector<unsigned char>& vector, int val);
	static std::vector<unsigned char> serializeStatusResponse(unsigned int status);

};

