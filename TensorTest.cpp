#include <iostream>
#include "OptionManager.h"
#include "AnalyzeCommand.h"
#include "CommandParser.h"
#include <filesystem>
#include <fstream>
#include <sstream> 
#include <ostream>
#include <queue>
#include <stack>
#include <algorithm>
using namespace std;
using namespace filesystem;

class Node {
public:
	string path;
	string fileName;
	vector<Node*> outNodes;
	bool isVisited = false;
	bool isExist = false;
	int iFrequency = 0;
	void addOutNode(Node* inNode) {  
		for (auto node : outNodes)
			if (node == inNode)
				return;
		outNodes.push_back(inNode); 
	}
	bool hasChilds(){
		return !outNodes.empty();
	}
	static void updateChildrenFrequencies(Node* inNode){
		for (auto node : inNode->outNodes) {
			node->iFrequency++;
			updateChildrenFrequencies(node);
		}
	}
	Node(string inPath) { path = inPath; }
};

class Analyzer {
private:
	AnalyzeCommand command;
	map<string, Node*> mNodes;
	stack<Node*> qQueue;
	void analyzeFile(Node* inNode) {
		inNode->isVisited = true;
		istringstream iss(readFile(inNode->path));
		string line;
		for (line; getline(iss, line);)
			analyzeRow(line, inNode);
	}
	void analyzeRow(string& input, Node* inNode) {
		if (input.find("#include") != string::npos) {
			string fileName = getFileName(input);
			string fullPath;
			
			if (input.find("\"") != string::npos)
				fullPath = findFile(fileName, true);
			else if (input.find("<") != string::npos)
				fullPath = findFile(fileName, false);

			string path = fullPath != "" ? fullPath : fileName;
			
			Node* pNode = nullptr;
			if (mNodes.find(path) != mNodes.end())
				pNode = mNodes[path];
			else{
				pNode = new Node(path);
				mNodes[path] = pNode;
				pNode->fileName = fileName;
			}
			pNode->iFrequency++;
			inNode->addOutNode(pNode);
			if (fullPath != "") {
				pNode->isExist = true;
				if (!pNode->isVisited)
					qQueue.push(pNode);
				else 
					Node::updateChildrenFrequencies(pNode);
			}
			else
				pNode->isExist = false;
		}
	}
	string findFile(string inFileName, bool isRelativePath) {
		vector<string> paths;
		if (isRelativePath) {
			paths.push_back(command.getCommandArguments().front());	
		}
		else {
			auto mOptionArguments = command.getOptionArguments();
			if (!mOptionArguments.empty()){
				auto directories = (*mOptionArguments.begin()).second;
				for (auto& directory : directories)
					paths.push_back(directory);
			}
		}

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
					if (index < input.size() && (input[index] != '\"' && input[index] != '<' && input[index] != '>'))
						if (input[index] != '\r')
							sFilename += input[index];

		return sFilename;
	}
	string readFile(string path) {
		ifstream file(path);
		string result;
		return result.assign(istreambuf_iterator<char>(file), istreambuf_iterator<char>());
	}
	void printTree(Node* inNode){
		static int iLevel = 0;
		for (auto node : inNode->outNodes) {
			for (int i = 0; i < iLevel * 2; i++)
				cout << ".";
			cout << node->fileName << (!node->isExist ? " (!)\n" : "\n");
			iLevel++;
			printTree(node);
			iLevel--;
		}
	}
	void printFrequencies() {
		vector<pair<int, string>> frequencies;
		for (auto entry : mNodes)
			frequencies.push_back(make_pair(entry.second->iFrequency, entry.second->fileName));
		std::sort(frequencies.begin(), frequencies.end(), [](pair<int, string> a, pair<int, string> b) {
			if (a.first > b.first)
				return true;
			else if (a.first == b.first && a.second < b.second)
				return true;
			else 
				return false;
		});
		for (auto entry : frequencies)
			cout << entry.second << " " << entry.first << "\n";
	}
public:
	void analyze(AnalyzeCommand inCommand) {
		command = inCommand;
		Node *pRoot = new Node(inCommand.getCommandArguments().front());

		for (auto & entry : directory_iterator(command.getCommandArguments().front()))
			if (entry.is_regular_file() && entry.path().extension() == ".cpp") {
				Node* pNode = new Node(entry.path().generic_string());
				pNode->fileName = entry.path().filename();
				pNode->isExist = true;
				mNodes[entry.path().generic_string()] = pNode;
				pRoot->addOutNode(pNode);
				qQueue.push(pNode);
			}
		
		while (!qQueue.empty()) {
			Node* pNode = qQueue.top();
			
			qQueue.pop();
			analyzeFile(pNode);
		}
		printTree(pRoot);
		cout << "\n";
		printFrequencies();
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