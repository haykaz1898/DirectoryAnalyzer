#pragma once
#include <string>
#include <vector>
#include "Option.h"
class OptionManager {
private:
	std::string sCommand;
	std::vector<Option*> vDefinedOptions;
public:
	void addNewOption(std::string inShortName, std::string inLongName, std::string inDescription, ArgumentType inOptionType, bool inIsSingleArg);
	std::vector<Option*> getDefinedOptions();
	Option* getOptionByName(std::string inName);

	bool checkOptionArguments(Option* inOption, std::vector<std::string> inArguments);
	bool checkForOption(std::string& inName);
	
	OptionManager(std::string inCommand);
	OptionManager();
	~OptionManager();
};