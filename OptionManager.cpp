#include "OptionManager.h"
using namespace std;

void OptionManager::addNewOption(string inShortName, string inLongName, string inDescription, ArgumentType inOptionType, bool inIsSingleArg) {
	vDefinedOptions.push_back(new Option(inShortName, inLongName, inDescription, inOptionType, inIsSingleArg));
}

std::vector<Option*> OptionManager::getDefinedOptions() { return vDefinedOptions; }

Option* OptionManager::getOptionByName(string inName) {
	for (auto option : vDefinedOptions)
		if (option->getLongName() == inName || option->getShortName() == inName)
			return option;
	return nullptr;
}

bool OptionManager::checkOptionArguments(Option* inOption, vector<string> inArguments) {
	if (inOption && inOption->isSingleArg() && inArguments.size() != 1
		|| inOption->getOptionType() == ArgumentType::NONE && inArguments.size() != 0
		|| inOption->getOptionType() == ArgumentType::REQUIRED && inArguments.size() == 0)
		return false;
	return true;
}
bool OptionManager::checkForOption(string& inName) {
	for (auto option : vDefinedOptions)
		if (option->getLongName() == inName)
			return false;
	return true;
}

OptionManager::OptionManager(string inCommand) { sCommand = inCommand; }
OptionManager::OptionManager() { }
OptionManager::~OptionManager() {
	for (auto option : vDefinedOptions)
		delete option;
	vDefinedOptions.clear();
}
