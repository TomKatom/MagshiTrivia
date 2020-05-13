#include "JsonResponsePacketSerializer.hpp"
#include <nlohmann/json.hpp>

using namespace nlohmann;

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(ErrorResponse res) {
	std::vector<unsigned char> buffer;
	int jsonDataLength = 0;
	json j;
	j["message"] = res.message;

	for (auto& c : j.dump()) {
		buffer.push_back(c);
	}

	jsonDataLength = buffer.size();
	buffer.insert(buffer.begin(), jsonDataLength & 0xff);
	buffer.insert(buffer.begin(), jsonDataLength >> 8 & 0xff);
	buffer.insert(buffer.begin(), jsonDataLength >> 16 & 0xff);
	buffer.insert(buffer.begin(), jsonDataLength >> 24 & 0xff);
	buffer.insert(buffer.begin(), loginResponseCode);
	return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(LoginResponse res) {
	std::vector<unsigned char> buffer;
	int jsonDataLength = 0;
	json j;
	j["status"] = res.status;

	for (auto& c : j.dump()) {
		buffer.push_back(c);
	}

	jsonDataLength = buffer.size();
	buffer.insert(buffer.begin(), jsonDataLength & 0xff);
	buffer.insert(buffer.begin(), jsonDataLength >> 8 & 0xff);
	buffer.insert(buffer.begin(), jsonDataLength >> 16 & 0xff);
	buffer.insert(buffer.begin(), jsonDataLength >> 24 & 0xff);
	buffer.insert(buffer.begin(), loginResponseCode);
	return buffer;
}
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(SignupResponse res) {
	std::vector<unsigned char> buffer;
	int jsonDataLength = 0;
	json j;
	j["status"] = res.status;

	for (auto& c : j.dump()) {
		buffer.push_back(c);
	}

	jsonDataLength = buffer.size();
	buffer.insert(buffer.begin(), jsonDataLength & 0xff);
	buffer.insert(buffer.begin(), jsonDataLength >> 8 & 0xff);
	buffer.insert(buffer.begin(), jsonDataLength >> 16 & 0xff);
	buffer.insert(buffer.begin(), jsonDataLength >> 24 & 0xff);
	buffer.insert(buffer.begin(), loginResponseCode);
	return buffer;
}

