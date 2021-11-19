#pragma once
#include <exception>
#include <string>
class InvalidDirectoryException : public std::exception {
protected:
	std::string sMsg;
public:
	const char* what() const throw() { return sMsg.c_str(); }
	InvalidDirectoryException(std::string inCommand, std::string inDirectory) { sMsg = inCommand + ": '" + inDirectory + "' : " + " No such directory"; } //TODO change to reference
};