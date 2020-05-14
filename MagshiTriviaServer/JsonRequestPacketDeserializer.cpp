#include "JsonRequestPacketDeserializer.hpp"
#include <algorithm>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

LoginRequest JsonRequestPacketDeserializer::deserializeLoginRequest(std::vector<unsigned char> buffer) {
	int jsonDataLength = ((buffer[1] << 8 | buffer[2]) << 8 | buffer[3]) << 8 | buffer[4]; //convert 4 bytes that represtns the length from buffer to integer
	std::string jsonData(buffer.begin(), buffer.end());
	jsonData = jsonData.substr(5, jsonDataLength);

	json j = json::parse(jsonData);

	LoginRequest loginRequest;
	loginRequest.userName = j["userName"];
	loginRequest.password = j["password"];
	return loginRequest;
}

SignupRequest JsonRequestPacketDeserializer::deserializeSignUpRequest(std::vector<unsigned char> buffer) {
	int jsonDataLength = ((buffer[1] << 8 | buffer[2]) << 8 | buffer[3]) << 8 | buffer[4]; //convert 4 bytes that represtns the length from buffer to integer
	std::string jsonData(buffer.begin(), buffer.end());
	jsonData = jsonData.substr(5, jsonDataLength);

	json j = json::parse(jsonData);

	SignupRequest signupRequest;
	signupRequest.username = j["userName"];
	signupRequest.password = j["password"];
	signupRequest.email = j["email"];
	return signupRequest;
}

RequestInfo JsonRequestPacketDeserializer::getRequestInfo(std::vector< unsigned char > buffer) {
	int jsonDataLength = ((buffer[1] << 8 | buffer[2]) << 8 | buffer[3]) << 8 | buffer[4]; //convert 4 bytes that represtns the length from buffer to integer

	std::vector<unsigned char> jsonData(buffer.begin() + 5, buffer.begin() + 5 + jsonDataLength);

	RequestInfo requestInfo;
	requestInfo.messageCode = buffer[0];
	requestInfo.jsonData = jsonData;
	return requestInfo;
}