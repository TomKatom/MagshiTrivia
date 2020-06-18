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
	return serializeStatusResponse(res.status);
}
std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(SignupResponse res) {
	return serializeStatusResponse(res.status);
}

std::vector<unsigned char>  JsonResponsePacketSerializer::serializeResponse(LogoutResponse res) {
	return serializeStatusResponse(res.status);
}

std::vector<unsigned char>  JsonResponsePacketSerializer::serializeResponse(GetRoomsResponse res) {
	std::vector<unsigned char> buffer;
	json j, temp;
	j["status"] = res.status;

	json roomsArray = json::array();


	for (int i = 0; i < res.rooms.size(); i++) {
		temp["name"] = res.rooms[i].name;
		temp["maxPlayers"] = res.rooms[i].maxPlayers;
		temp["timePerQuestion"] = res.rooms[i].timePerQuestion;

		roomsArray[i] = temp;
	}

	j["Rooms"] = roomsArray;

	for (auto& c : j.dump()) {
		buffer.push_back(c);
	}

	JsonResponsePacketSerializer::insertInt2Vector(buffer, buffer.size());
	buffer.insert(buffer.begin(), logoutResponseCode);
	return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetPlayersInRoomResponse res) {
	std::vector<unsigned char> buffer;
	json j;
	j["PlayersInRoom"] = res.players;

	for (auto& c : j.dump()) {
		buffer.push_back(c);
	}

	JsonResponsePacketSerializer::insertInt2Vector(buffer, buffer.size());
	buffer.insert(buffer.begin(), logoutResponseCode);
	return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(JoinRoomResponse res) {
	return serializeStatusResponse(res.status);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(CreateRoomResponse res) {
	return serializeStatusResponse(res.status);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetStatisticsResponse res) {
	std::vector<unsigned char> buffer;
	json j, userStatisticsJson, temp;
	json highScoresJson = json::array();

	userStatisticsJson["numOfPlayerGames"] = res.userStatistics.numOfPlayerGames;
	userStatisticsJson["numOfTotalAnswers"] = res.userStatistics.numberOfTotalAnswers;
	userStatisticsJson["numOfCorrectAnswers"] = res.userStatistics.numOfCorrectAnswers;
	userStatisticsJson["correctAnswersPercentage"] = res.userStatistics.correctAnswersPercentage;


	for (int i = 0; i < res.highScores.size(); i++) {
		temp["playerName"] = res.highScores[i].playerName;
		temp["playerScore"] = res.highScores[i].playerScore;
	
		highScoresJson[i] = temp;
	}


	j["userStatistics"] = userStatisticsJson;
	j["highScores"] = highScoresJson;

	return j;
}

std::vector<unsigned char>  JsonResponsePacketSerializer::serializeResponse(CloseRoomResponse res) {
	return serializeStatusResponse(res.status);
}

std::vector<unsigned char>  JsonResponsePacketSerializer::serializeResponse(StartRoomResponse res) {
	return serializeStatusResponse(res.status);
}


std::vector<unsigned char>  JsonResponsePacketSerializer::serializeResponse(GetRoomStateResponse res) {
	std::vector<unsigned char> buffer;
	json j, temp;
	json playersJson = json::array();

	for (int i = 0; i < res.players.size(); i++) {
		playersJson[i] = res.players[i];
	}

	j["status"] = res.status;
	j["hasGameBegun"] = res.hasGameBegun;
	j["players"] = playersJson;
	j["questionCount"] = res.questionCount;
	j["answerTimeout"] = res.answerTimeout;

	return j;
}

std::vector<unsigned char>  JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse res) {
	return serializeStatusResponse(res.status);
}




//Helper functions
void JsonResponsePacketSerializer::insertInt2Vector(std::vector<unsigned char>& vector, int val) {
	vector.insert(vector.begin(), val & 0xff);
	vector.insert(vector.begin(), val >> 8 & 0xff);
	vector.insert(vector.begin(), val >> 16 & 0xff);
	vector.insert(vector.begin(), val >> 24 & 0xff);
}	

std::vector<unsigned char> JsonResponsePacketSerializer::serializeStatusResponse(unsigned int status) {
	std::vector<unsigned char> buffer;
	json j;
	j["status"] = status;

	for (auto& c : j.dump()) {
		buffer.push_back(c);
	}

	JsonResponsePacketSerializer::insertInt2Vector(buffer, buffer.size());
	buffer.insert(buffer.begin(), logoutResponseCode);
	return buffer;
}
