#include "Command.h"
using namespace std;

void Command::setCommand(string inCommandName) { sCommand = inCommandName; }
string Command::getCommand() { return sCommand; }

void Command::addCommandArgument(string inArgument) { vCommandArguments.push_back(inArgument); }
//TODO return pointer
vector<string> Command::getCommandArguments() { return vCommandArguments; }

void Command::addOptionArgument(string inOption, string inArgument) { mOptionArguments[inOption].push_back(inArgument); }
//TODO return pointer
map<string, vector<string>> Command::getOptionArguments() { return mOptionArguments; }
