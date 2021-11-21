#include "CommandParser.h"
#include <vector>
using namespace std;
std::string CommandParser::getOption(string input) {
	if (input[0] == '-' && input[1] != '-')
		return string(1, input[0]) + string(1, input[1]);
	else if (input[0] == '-' && input[1] == '-')
		return input;
	return "";
}

void CommandParser::parse(int argc, char** argv, OptionManager& optionManager, Command* outCommand) {
	vector<string> arguments;

	vector<pair<string, vector<string>>> vOptionArguments;
	int startIndex = 1;
	while (startIndex < argc) {
		string sOption = getOption(argv[startIndex]);
		if (sOption != "") {
			startIndex += 1;
			while (startIndex < argc) {
				if (getOption(argv[startIndex]) == "")
					outCommand->addOptionArgument(sOption, argv[startIndex]);
				else if (getOption(argv[startIndex]) != sOption)
					break;
				startIndex++;
			}
		}
		else if (outCommand->getOptionArguments()->empty())
			outCommand->addCommandArgument(argv[startIndex]);
		startIndex++;
	}
}
