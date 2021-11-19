#pragma once
#include <string>
enum ArgumentType {
	NONE,
	REQUIRED,
	OPTIONAL
};

class Option {
private:
	std::string sShortName;
	std::string sLongName;
	std::string sDescription;
	ArgumentType eArgumentType;
	bool bIsSingleArg;
public:
	std::string getShortName();
	std::string getLongName();
	std::string getDescription();
	ArgumentType getOptionType();
	bool isSingleArg();
	std::string toString();
	Option(std::string inShortName, std::string inLongName, std::string inDescription, ArgumentType inOptionType, bool inIsSingleArg);
};