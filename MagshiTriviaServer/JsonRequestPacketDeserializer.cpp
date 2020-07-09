#include "JsonRequestPacketDeserializer.hpp"
#include <algorithm>



json JsonRequestPacketDeserializer::getJsonFromBuffer(std::vector< unsigned char > buffer) {
	int jsonDataLength = ((buffer[1] << 8 | buffer[2]) << 8 | buffer[3]) << 8 | buffer[4]; //convert 4 bytes that represtns the length from buffer to integer
	std::string jsonData(buffer.begin(), buffer.end());
	jsonData = jsonData.substr(5, jsonDataLength);

	json j = json::parse(jsonData);

	return j;
}

RequestInfo JsonRequestPacketDeserializer::getRequestInfo(std::vector< unsigned char > buffer) {
	RequestInfo requestInfo;
	requestInfo.messageCode = buffer[0];
	requestInfo.buffer = buffer;
	return requestInfo;
}


LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<unsigned char> buffer) {	
	json j = JsonRequestPacketDeserializer::getJsonFromBuffer(buffer);
	LoginRequest loginRequest;
	loginRequest.userName = j["username"];
	loginRequest.password = j["password"];
	return loginRequest;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignUpRequest(std::vector<unsigned char> buffer) {
	json j = JsonRequestPacketDeserializer::getJsonFromBuffer(buffer);

	SignupRequest signupRequest;
	signupRequest.username = j["username"];
	signupRequest.password = j["password"];
	signupRequest.email = j["email"];
	return signupRequest;
}



GetPlayersInRoomRequest JsonRequestPacketDeserializer::deserializeGetPlayersInRoomRequest(std::vector< unsigned char > buffer) {
	json j = JsonRequestPacketDeserializer::getJsonFromBuffer(buffer);

	GetPlayersInRoomRequest req;
	req.roomId = j["roomId"];
	return req;
}

JoinRoomRequest JsonRequestPacketDeserializer::deserializeJoinRoomRequest(std::vector< unsigned char > buffer) {
	json j = JsonRequestPacketDeserializer::getJsonFromBuffer(buffer);

	JoinRoomRequest req;
	req.roomId = j["roomId"];
	return req;
}

CreateRoomRequest JsonRequestPacketDeserializer::deserializeCreateRoomRequest(std::vector< unsigned char > buffer) {
	json j = JsonRequestPacketDeserializer::getJsonFromBuffer(buffer);

	CreateRoomRequest req;
	req.roomName = j["roomName"];
	req.maxUsers = j["maxUsers"];
	req.questionCount = j["questionCount"];
	req.answerTimeout = j["answerTimeout"];
	return req;	
}

LogoutRequest JsonRequestPacketDeserializer::deserializeLogoutRequest(std::vector<unsigned char> buffer) {
	json j = JsonRequestPacketDeserializer::getJsonFromBuffer(buffer);

	LogoutRequest logoutRequest;
	logoutRequest.username = j["name"];
	return logoutRequest;
}