#pragma once
#include <string>
#include <vector>


class IRequestHandler;
class Communicator;

typedef struct RequestInfo {
	unsigned char messageCode;
	//time
	std::vector<unsigned char> jsonData;
} RequestInfo;

typedef struct RequestResult {

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


enum ResponseCodes { 
	loginResponseCode =0, 
	signupResponseCode
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
