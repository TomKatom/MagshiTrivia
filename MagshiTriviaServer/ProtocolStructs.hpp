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

typedef struct GetStatisticsResponse {
	unsigned int status;
	UserStatistics userStatistics;
	std::vector<HighScore> highScores;

}GetStatisticsResponse;

typedef struct UserStatistics {
	unsigned long numOfPlayerGames;
	unsigned long numOfCorrectAnswers;
	unsigned long numberOfTotalAnswers;
	double correctAnswersPercentage;
}UserStatistics;

typedef struct HighScore {
	std::string playerName;
	unsigned long long playerScore;
}GetPlayersInRoomRequest;

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

enum ResponseCodes { 
	loginResponseCode =0, 
	signupResponseCode,
	logoutResponseCode
};

enum ResponseStatus {
	loginSuccess = 0,
	loginError,
	SignUpSuccess,
	SignUpError
};
	//Login and Signup
	//unsigned char loginResponseCode = 0;
	//unsigned char signupResponseCode = 1;


	//Error
	//unsigned char errorResponseCode = 16;

enum RequestCodes {
	loginRequestCode = 20, 
	signupRequestCode
};
	//Login and Signup
	//unsigned char loginRequestCode = 20;
	//unsigned char signupRequestCode = 21;
