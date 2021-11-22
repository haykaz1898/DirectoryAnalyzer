#include "AnalyzeCommand.h"
#include "CommandParser.h"
#include "exception"
#include <iostream>

int main(int argc, char **argv) {
	AnalyzeCommand* pCommand = new AnalyzeCommand();
	CommandParser::parse(argc, argv, pCommand);
	try {
		pCommand->run();
	}
	catch (std::exception& e) {
		std::cout << e.what();
	}
	return 0;
}