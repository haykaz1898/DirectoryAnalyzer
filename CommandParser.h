#pragma once
#include <string>
#include "Command.h"
class CommandParser {
private:
	static std::string getOption(std::string input);
public:
	static void parse(int argc, char** argv, Command* outCommand);
};