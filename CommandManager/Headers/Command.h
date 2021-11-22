#pragma once
#include <string>
#include <map>
#include <vector>

class Command {
protected:
	std::string sCommand;
	std::vector<std::string>* vCommandArguments;
	std::map<std::string, std::vector<std::string>*>* mOptionArguments;
public:
	void setCommand(std::string inCommandName);
	std::string getCommand();

	void addCommandArgument(std::string inArgument);
	std::vector<std::string>* getCommandArguments();
	
	void addOptionArgument(std::string inOption, std::string inArgument);
	std::map<std::string, std::vector<std::string>*>* getOptionArguments();

	virtual void run() = 0;
	virtual void validate() = 0;
	Command();
	virtual ~Command();
};
