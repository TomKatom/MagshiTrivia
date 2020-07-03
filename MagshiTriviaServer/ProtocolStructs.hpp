#pragma once
#include <string>
#include <vector>
#include "Room.hpp"

class IRequestHandler;
class Communicator;

typedef struct RequestInfo {
	unsigned char messageCode;
	//time
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




enum ResponseCodes { 
	loginResponseCode =0, 
	signupResponseCode,
	logoutResponseCode
};

enum ResponseStatus {
	loginSuccess = 0,
	loginError,
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
	gameStarted
};

enum RequestCodes {
	loginRequestCode = 20, 
	signupRequestCode,
	createRoomRequest,
	getRoomsRequest,
	getPlayersInRoomRequest,
	joinRoomRequest,
	getStatisticsRequest,
	logoutRequest,
	closeRoomRequest,
	startGameRequest,
	getRoomStateRequest,
	leaveRoomRequest
};

