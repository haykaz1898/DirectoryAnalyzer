#include "Command.h"
using namespace std;

void Command::setCommand(string inCommandName) { sCommand = inCommandName; }
string Command::getCommand() { return sCommand; }

void Command::addCommandArgument(string inArgument) { vCommandArguments->push_back(inArgument); }
//TODO return pointer
vector<string>* Command::getCommandArguments() { return vCommandArguments; }

void Command::addOptionArgument(string inOption, string inArgument) { 
    if (mOptionArguments->find(inOption) != mOptionArguments->end()) 
        (*mOptionArguments)[inOption]->push_back(inArgument);
    else {
        vector<string>* vArguments = new vector<string>();
        vArguments->push_back(inArgument);
        mOptionArguments->insert(make_pair(inOption, vArguments));
    }
}
//TODO return pointer
map<string, vector<string>*>* Command::getOptionArguments() { return mOptionArguments; }

Command::Command(){
    mOptionArguments = new map<string,vector<string>*>();
    vCommandArguments = new vector<string>();
}
Command::~Command(){
    for (auto entry : *mOptionArguments)
        delete entry.second;
    delete mOptionArguments;
    delete vCommandArguments;
}