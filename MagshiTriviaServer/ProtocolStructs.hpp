#pragma once
#include <string>
#include <vector>
#include <map>
#include "Room.hpp"
#include <ctime>
#include <cmath>

class IRequestHandler;
class Communicator;

typedef struct RequestInfo {
	unsigned char messageCode;
	std::time_t receivalTime;
	std::vector<unsigned char> buffer;
} RequestInfo;

typedef struct RequestResult {
	std::vector<unsigned char> buffer;
	IRequestHandler* irequestHandler;
}RequestResult;

typedef struct ErrorResponse {
	std::string message;
}ErrorResponse;

typedef struct LoginResponse {
	unsigned int status;
}LoginResponse;

typedef struct SignupResponse {
	unsigned int status;
}SignupResponse;

typedef struct SignUpRequest {
	std::string  username;
	std::string password;
	std::string email;
}SignupRequest;

typedef struct LoginRequest {
	std::string userName;
	std::string password;
}LoginRequest;




typedef struct LogoutResponse {
	unsigned int status;
}LogoutResponse;

typedef struct GetRoomsResponse {
	unsigned int status;
	std::vector<Room> rooms;
}GetRoomsResponse;

typedef struct GetPlayersInRoomResponse {
	std::vector<std::string> players;
}GetPlayersInRoomResponse;

typedef struct JoinRoomResponse {
	unsigned int status;
}JoinRoomResponse;

typedef struct CreateRoomResponse {
	unsigned int roomId;
	unsigned int status;
}CreateRoomResponse;

typedef struct UserStatistics {
	unsigned int numOfPlayerGames;
	unsigned int numOfCorrectAnswers;
	unsigned int numberOfTotalAnswers;
	double averageTimeForAnswer;
}UserStatistics;

typedef struct HighScore {
	std::string playerName;
	unsigned int playerScore;
}HighScore;

typedef struct GetStatisticsResponse {
	unsigned int status;
	UserStatistics userStatistics;
}GetStatisticsResponse;

typedef struct LeaderboardEntry {
	std::string username;
	unsigned int numOfGames;
	unsigned int totalWins;
	unsigned int totalLosses;
	bool operator>(const LeaderboardEntry& other) const { double thisWinrate = (double)this->totalWins / (double)this->totalLosses; double otherWinrate = (double)other.totalWins / (double)other.totalLosses; return thisWinrate > otherWinrate; }
}LeaderboardEntry;

typedef struct GetLeaderboardResponse {
	unsigned int status;
	std::vector<LeaderboardEntry> players;
}GetLeaderboardResponse;


typedef struct LogoutRequest {
	std::string username;
}LogoutRequest;

typedef struct GetPlayersInRoomRequest {
	unsigned int roomId;
}GetPlayersInRoomRequest;

typedef struct JoinRoomRequest {
	unsigned int roomId;
}JoinRoomRequest;

typedef struct CreateRoomRequest {
	std::string roomName;
	unsigned int maxUsers;
	unsigned int questionCount;
	unsigned int answerTimeout;
}CreateRoomRequest;

//V3
typedef struct CloseRoomResponse {
	unsigned int status;
}CloseRoomResponse;

typedef struct StartGameResponse {
	unsigned int status;
}StartGameResponse;

typedef struct GetRoomStateResponse {
	unsigned int status;
	int id;
	bool hasGameBegun;
	std::string name;
	std::vector<std::string> players;
	unsigned int maxPlayers;
	unsigned int questionCount;
	unsigned int answerTimeout;
}GetRoomStateResponse;

typedef struct LeaveRoomResponse {
	unsigned int status;
}LeaveRoomResponse;


//V4
typedef struct LeaveGameResponse {
	unsigned int status;
} LeaveGameResponse;
typedef struct PlayerResults {
	std::string username;
	unsigned int correctAnswerCount;
	unsigned int wrongAnswerCount;
	long double averageAnswerTime;
	bool operator<(const PlayerResults& other) const { return (double)this->correctAnswerCount / this->averageAnswerTime < (double)other.correctAnswerCount / other.averageAnswerTime; }
	bool operator>(const PlayerResults& other) const { return (double)this->correctAnswerCount / this->averageAnswerTime > (double)other.correctAnswerCount / other.averageAnswerTime; }
}PlayerResults;

typedef struct GetGameResultsResponse {
	unsigned int status;
	std::vector<PlayerResults> results;
}GetGameResultsResponse;

typedef struct SubmitAnswerResponse {
	unsigned int status;
	unsigned int correctAnswerId;
}SubmitAnswerResponse;

typedef struct GetQuestionResponse {
	unsigned int status;
	std::string question;
	std::vector<std::string> answers;
}GetQuestionResponse;

typedef struct SubmitAnswerRequest {
	unsigned answerId;
};

typedef struct GetLastUserResponse {
	std::string username;
} GetLastUserResposne;



enum ResponseCodes { 
	loginResponseCode =0, 
	signupResponseCode,
	logoutResponseCode
};

enum ResponseStatus {
	loginSuccess = 0,
	loginError,
	alreadyLoggedIn,
	signUpSuccess,
	signUpError,
	logoutSuccess,
	logoutError,
	getRoomsSuccess,
	getRoomsError,
	joinRoomSuccess,
	joinRoomError,
	createRoomSuccess,
	createRoomError,
	closeRoomSuccess,
	closeRoomError,
	startGameSuccess,
	startGameError,
	getRoomStateSuccess,
	getRoomStateError,
	leaveRoomSuccess,
	leaveRoomError,
	roomClosed,
	gameStarted,
	leaveGameSuccess,
	leaveGameError,
	getQuestionSuccess,
	getQuestionError,
	submitAnswerSuccess,
	submitAnswerError,
	getGameResultSuccess,
	getGameResultError,
	gameHasNotEnded
};

enum RequestCodes {
	loginRequestCode = 20, 
	signupRequestCode,
	createRoomRequest,
	getRoomsRequest,
	getPlayersInRoomRequest,
	joinRoomRequest,
	getStatisticsRequest,
	getLeaderboardRequest,
	getLastUser,
	logoutRequest,
	closeRoomRequest,
	startGameRequest,
	getRoomStateRequest,
	leaveRoomRequest,
	leaveGameRequest,
	getQuestionRequest,
	submitAnswerRequest,
	getGameResultRequest
};

