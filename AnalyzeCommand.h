#pragma once
#include "Command.h"
#include "OptionManager.h"
class AnalyzeCommand : public Command {
private:
	OptionManager* pOptionManager;
public:
	void validate();
	AnalyzeCommand();
};