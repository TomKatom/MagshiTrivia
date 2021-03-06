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
		temp["id"] = res.rooms[i].getID();
		temp["name"] = res.rooms[i].getName();
		temp["maxPlayers"] = res.rooms[i].getMaxPlayers();
		temp["timePerQuestion"] = res.rooms[i].getTimePerQuestion();
		temp["questionsCount"] = res.rooms[i].getQuestionsCount();

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
	j["players"] = res.players;

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
	std::vector<unsigned char> buffer;
	json j;
	j["status"] = res.status;
	j["roomId"] = res.roomId;

	for (auto& c : j.dump()) {
		buffer.push_back(c);
	}

	JsonResponsePacketSerializer::insertInt2Vector(buffer, buffer.size());
	buffer.insert(buffer.begin(), logoutResponseCode);
	return buffer;
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetStatisticsResponse res) {
	std::vector<unsigned char> buffer;
	json j;

	j["numOfPlayerGames"] = res.userStatistics.numOfPlayerGames;
	j["numOfTotalAnswers"] = res.userStatistics.numberOfTotalAnswers;
	j["numOfCorrectAnswers"] = res.userStatistics.numOfCorrectAnswers;
	j["averageTimeForAnswer"] = res.userStatistics.averageTimeForAnswer;
	for (auto& c : j.dump()) {
		buffer.push_back(c);
	}

	JsonResponsePacketSerializer::insertInt2Vector(buffer, buffer.size());
	buffer.insert(buffer.begin(), logoutResponseCode);
	return buffer;
}

std::vector<unsigned char>  JsonResponsePacketSerializer::serializeResponse(CloseRoomResponse res) {
	return serializeStatusResponse(res.status);
}

std::vector<unsigned char>  JsonResponsePacketSerializer::serializeResponse(StartGameResponse res) {
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
	j["maxPlayers"] = res.maxPlayers;
	j["name"] = res.name;
	j["id"] = res.id;

	for (auto& c : j.dump()) {
		buffer.push_back(c);
	}

	JsonResponsePacketSerializer::insertInt2Vector(buffer, buffer.size());
	buffer.insert(buffer.begin(), logoutResponseCode);

	return buffer;
}

std::vector<unsigned char>  JsonResponsePacketSerializer::serializeResponse(LeaveRoomResponse res) {
	return serializeStatusResponse(res.status);
}

std::vector<unsigned char>  JsonResponsePacketSerializer::serializeResponse(GetGameResultsResponse res) {
	std::vector<unsigned char> buffer;
	json j, temp;
	j["status"] = res.status;

	json resultsArray = json::array();


	for (int i = 0; i < res.results.size(); i++) {
		temp["username"] = res.results[i].username;
		temp["correctAnswerCount"] = res.results[i].correctAnswerCount;
		temp["wrongAnswerCount"] = res.results[i].wrongAnswerCount;
		temp["averageAnswerTime"] = res.results[i].averageAnswerTime;
	
		resultsArray[i] = temp;
	}

	j["results"] = resultsArray;

	for (auto& c : j.dump()) {
		buffer.push_back(c);
	}

	JsonResponsePacketSerializer::insertInt2Vector(buffer, buffer.size());
	buffer.insert(buffer.begin(), logoutResponseCode);
	return buffer;
}

std::vector<unsigned char>  JsonResponsePacketSerializer::serializeResponse(SubmitAnswerResponse res) {
	std::vector<unsigned char> buffer;
	json j;
	j["status"] = res.status;
	j["correctAnswerId "] = res.correctAnswerId;

	for (auto& c : j.dump()) {
		buffer.push_back(c);
	}

	JsonResponsePacketSerializer::insertInt2Vector(buffer, buffer.size());
	buffer.insert(buffer.begin(), logoutResponseCode);
	return buffer;
}
std::vector<unsigned char>  JsonResponsePacketSerializer::serializeResponse(GetLastUserResponse res) {
	std::vector<unsigned char> buffer;
	json j;
	j["lastUser"] = res.username;

	for (auto& c : j.dump()) {
		buffer.push_back(c);
	}

	JsonResponsePacketSerializer::insertInt2Vector(buffer, buffer.size());
	buffer.insert(buffer.begin(), logoutResponseCode);
	return buffer;
}

std::vector<unsigned char>  JsonResponsePacketSerializer::serializeResponse(GetQuestionResponse res) {
	std::vector<unsigned char> buffer;
	json j;
	j["status"] = res.status;
	j["question"] = res.question;
	j["answers"] = res.answers;
	for (auto& c : j.dump()) {
		buffer.push_back(c);
	}

	JsonResponsePacketSerializer::insertInt2Vector(buffer, buffer.size());
	buffer.insert(buffer.begin(), logoutResponseCode);
	return buffer;
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

std::vector<unsigned char>  JsonResponsePacketSerializer::serializeResponse(LeaveGameResponse res) {
	return serializeStatusResponse(res.status);
}

std::vector<unsigned char> JsonResponsePacketSerializer::serializeResponse(GetLeaderboardResponse res) {

	std::vector<unsigned char> buffer;
	json j, temp;
	j["status"] = res.status;

	json playersArray = json::array();


	for (int i = 0; i < res.players.size(); i++) {
		temp["username"] = res.players[i].username;
		temp["totalWins"] = res.players[i].totalWins;
		temp["totalLosses"] = res.players[i].totalLosses;
		temp["numOfGames"] = res.players[i].numOfGames;
	
		playersArray[i] = temp;
	}

	j["players"] = playersArray;

	for (auto& c : j.dump()) {
		buffer.push_back(c);
	}

	JsonResponsePacketSerializer::insertInt2Vector(buffer, buffer.size());
	buffer.insert(buffer.begin(), logoutResponseCode);
	return buffer;
}
