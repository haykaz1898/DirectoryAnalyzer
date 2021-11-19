#include "AnalyzeCommand.h"
#include <filesystem>
#include "InvalidDirectoryException.h"
#include "InvalidOptionException.h"

using namespace std;
using namespace filesystem;

void AnalyzeCommand::validate() {
	for (auto directory : vCommandArguments)
		if (!is_directory(directory))
			throw InvalidDirectoryException("Analyze", directory);

	for (auto option : mOptionArguments) {
		Option* pOption = pOptionManager->getOptionByName(option.first);
		if (pOptionManager && pOptionManager->checkOptionArguments(pOption, option.second)) {
			for (auto directory : option.second)
				if (!is_directory(directory))
					throw InvalidDirectoryException("Analyze", directory);
		}
		else
			throw InvalidOptionException("Analyze", option.first);
	}
}
AnalyzeCommand::AnalyzeCommand() {
	pOptionManager = new OptionManager("Analyze");
	pOptionManager->addNewOption("-I", "", "Sources search path", ArgumentType::OPTIONAL, false);
	pOptionManager->addNewOption("", "--help", "Help", ArgumentType::NONE, false);
}
