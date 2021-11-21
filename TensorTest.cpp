#include "OptionManager.h"
#include "AnalyzeCommand.h"
#include "CommandParser.h"
#include "Analyzer.h"
#include "exception"
#include <iostream>

int main(int argc, char **argv) {
	OptionManager manager("Analyze");
	AnalyzeCommand* pCommand = new AnalyzeCommand();
	CommandParser::parse(argc, argv, manager, pCommand);
	try {
		pCommand->validate();
		Analyzer analyzer(pCommand);
		analyzer.Analyze();
	}
	catch (std::exception& e) {
		std::cout << e.what();
	}
	return 0;
}