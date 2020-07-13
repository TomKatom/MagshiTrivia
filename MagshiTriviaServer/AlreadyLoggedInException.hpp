#pragma once
#include <exception>

class AlreadyLoggedInException : std::exception {
	const char* what() const throw ()
	{
		return "User already logged in.";
	}
};
