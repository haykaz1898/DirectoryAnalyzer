#pragma once
#include <string>
#include "Command.h"
#include "OptionManager.h"
class CommandParser {
private:
	static std::string getOption(std::string input);
public:
	static void parse(int argc, char** argv, OptionManager& optionManager, Command& outCommand);
};