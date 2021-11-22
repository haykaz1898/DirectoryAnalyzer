#pragma once
#include <exception>
#include <string>

class InvalidOptionException : public std::exception {
protected:
	std::string sMsg;
public:
	const char* what() const throw() { return sMsg.c_str(); }
	InvalidOptionException(std::string inCommand, std::string inOption) { sMsg = inCommand + ": invalid option -- '" + inOption + "'"; } //TODO change to reference
};