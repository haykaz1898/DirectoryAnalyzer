#include <iostream>
#include "OptionManager.h"
#include "AnalyzeCommand.h"
#include "CommandParser.h"
#include <filesystem>
#include <fstream>
#include <sstream> 
#include <ostream>
#include <queue>
using namespace std;
using namespace filesystem;

class Node {
public:
	string path;
	vector<Node*> inNodes;
	vector<Node*> outNodes;
	bool isVisited = false;
	bool isExist = false;
	
	void addOutNode(Node* inNode) { outNodes.push_back(inNode); }

	Node(string inPath) { path = inPath; }
};

class Analyzer {
private:
	AnalyzeCommand command;
	Node* root;
	map<string, Node*> mNodes;
	queue<Node*> queue;
	void analyzeFile(Node* inNode) {
		inNode->isVisited = true;
		istringstream iss(readFile(inNode->path));
		string line;
		for (line; getline(iss, line);)
			analyzeRow(line, inNode);
	}
	void analyzeRow(string& input, Node* inNode) 
	{
		if (input.find("#include") != string::npos) {
			if (input.find("\"") != string::npos) {
				string fileName = getFileName(input);
				string fullPath = findFile(fileName, true);
				if (fullPath != "") {
					Node* pNode = nullptr;

					if (mNodes.find(fullPath) != mNodes.end())
						pNode = mNodes[fullPath];
					else {
						pNode = new Node(fullPath);
						mNodes[fullPath] = pNode;
					}

					inNode->isExist = true;
					inNode->addOutNode(pNode);
				}
				else
					inNode->isExist = false;
					
			}
			else if (input.find("<") != string::npos) {
			}
		}
	}
	string findFile(string inFileName, bool isRelativePath) {
		vector<string> paths;
		if (isRelativePath) {
			paths.push_back(command.getCommandArguments().front());	
		}
		else
			for (auto& directory : (*command.getOptionArguments().begin()).second)
				paths.push_back(directory);

		for (auto& directory : paths)
			for (auto& entry : directory_iterator(directory))
				if (entry.is_regular_file() && entry.path().filename() == inFileName)
					return entry.path().generic_string();

		return "";
	}
	string getFileName(string& input) {
		string sFilename;
		for (int index = 0; index < input.size(); index++)
			if (input[index] == '"' || input[index] == '<')
				for (; index < input.size(); index++)
					if (index < input.size() && (input[index] != '\"' && input[index] != '>'))
						sFilename += input[index];

		return sFilename;
	}
	string readFile(string path) {
		ifstream file(path);
		string result;
		return result.assign(istreambuf_iterator<char>(file), istreambuf_iterator<char>());
	}
public:
	vector<string> analyze(AnalyzeCommand inCommand) {
		command = inCommand;
		root = new Node(inCommand.getCommandArguments().front());

		for (auto & entry : directory_iterator(command.getCommandArguments().front()))
			if (entry.is_regular_file() && entry.path().extension() == ".cpp") {
				Node* pNode = new Node(entry.path().generic_string());
				pNode->isExist = true;
				mNodes[entry.path().generic_string()] = pNode;
				root->addOutNode(pNode);
				queue.push(pNode);
			}
		
		while (!queue.empty()) {
			Node* pNode = queue.front();
			queue.pop();
			if (!pNode->isVisited)
				analyzeFile(pNode);
		}
		return vector<string>();
	}
};

int main(int argc, char **argv)
{
	OptionManager manager("Analyze");
	AnalyzeCommand command;
	CommandParser::parse(argc, argv, manager, command);
	try {
		command.validate();
		Analyzer analyzer;
		analyzer.analyze(command);
	}
	catch (exception& e) {
		cout << e.what();
	}
	
	return 0;
}