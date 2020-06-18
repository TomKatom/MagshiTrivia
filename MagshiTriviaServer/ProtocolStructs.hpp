#pragma once
#include <string>
#include <vector>
#include "RoomData.hpp"

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
	std::vector<RoomData> rooms;
}GetRoomsResponse;

typedef struct GetPlayersInRoomResponse {
	std::vector<std::string> players;
}GetPlayersInRoomResponse;

typedef struct JoinRoomResponse {
	unsigned int status;
}JoinRoomResponse;

typedef struct CreateRoomResponse {
	unsigned int status;
}CreateRoomResponse;

typedef struct UserStatistics {
	unsigned int numOfPlayerGames;
	unsigned int numOfCorrectAnswers;
	unsigned int numberOfTotalAnswers;
	double correctAnswersPercentage;
}UserStatistics;

typedef struct HighScore {
	std::string playerName;
	unsigned int playerScore;
}HighScore;

typedef struct GetStatisticsResponse {
	unsigned int status;
	UserStatistics userStatistics;
	std::vector<HighScore> highScores;
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

typedef struct StartRoomResponse {
	unsigned int status;
}StartRoomResponse;

typedef struct GetRoomStateResponse {
	unsigned int status;
	bool hasGameBegun;
	std::vector<std::string> players;
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
	createRoomError
};
	//Login and Signup
	//unsigned char loginResponseCode = 0;
	//unsigned char signupResponseCode = 1;


	//Error
	//unsigned char errorResponseCode = 16;

enum RequestCodes {
	loginRequestCode = 20, 
	signupRequestCode,
	createRoomRequest,
	getRoomsRequest,
	getPlayersInRoomRequest,
	joinRoomRequest,
	getStatisticsRequest,
	logoutRequest
};
	//Login and Signup
	//unsigned char loginRequestCode = 20;
	//unsigned char signupRequestCode = 21;
