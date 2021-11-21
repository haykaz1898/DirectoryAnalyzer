#include "Analyzer.h"
#include <stack>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include <filesystem>

using namespace std;
using namespace filesystem;

void Analyzer::populateTree(string inFile){
    stack<string> oStack;
	oStack.push(inFile);
	vector<bool> isVisited;
	while (!oStack.empty()) {
		Node* pCurrentNode = pTree->getNode(oStack.top());
		pTree->setIsVisited(pCurrentNode);
		stringstream oStringStream(readFile(pCurrentNode->getPath()));
		oStack.pop();
		string sLine;
		for (sLine; getline(oStringStream, sLine);) {
			if (sLine.find("#include") != string::npos) {
				bool bFileExist = false;
				string sFileName = parseFileName(sLine);
				string sFilePath = getFilePath(sFileName, sLine.find("\"") != string::npos);
				if (sFilePath != "") 
					bFileExist = true;
				else
					sFilePath = sFileName;
				auto node = pTree->addNewNode(sFileName, sFilePath);
				pTree->addNodeToParent(pCurrentNode, node);
				if (!pTree->isVisited(node)) {
					node->increaseFrequency(1);
					if (bFileExist) {
						node->setFileExist(bFileExist);
						oStack.push(sFilePath);
					}
				}
				else 
					pTree->updateFrequencies(node);
			}
		}
	
	}
}
string Analyzer::getFilePath(string inFileName, bool isRelativePath) {
	vector<string> vPaths;
	if (isRelativePath)
		vPaths.push_back(pCommand->getCommandArguments()->front());
	else{
		auto vOptionArgs = pCommand->getOptionArguments();
		if (vOptionArgs->begin() != vOptionArgs->end()) 
			for (auto path : *(*vOptionArgs->begin()).second)
				vPaths.push_back(path);
	}
	for (auto path : vPaths){
		for (auto& entry : directory_iterator(path))
			if (entry.path().filename() == inFileName)
				return entry.path().generic_string();
	}
	return "";
}
string Analyzer::parseFileName(string& inLine){
	string sFilename;
	for (int index = 0; index < inLine.size(); index++)
		if (inLine[index] == '"' || inLine[index] == '<')
			for (; index < inLine.size(); index++)
				if (index < inLine.size() 
					&& inLine[index] != '\"' 
					&& inLine[index] != '<' 
					&& inLine[index] != '>')
					if (inLine[index] != '\r')
						sFilename += inLine[index];
	return sFilename;
}
string Analyzer::readFile(string path) {
	ifstream file(path);
	string result;
	return result.assign(istreambuf_iterator<char>(file), istreambuf_iterator<char>());
}

void Analyzer::Analyze() {
	for (auto & entry : directory_iterator(pCommand->getCommandArguments()->front()))
		if (entry.is_regular_file() && entry.path().extension() == ".cpp") {
			auto pNode = pTree->addNewNode(entry.path().filename().generic_string(), entry.path().generic_string());
			pNode->setFileExist(true);
			populateTree(entry.path());
			pTree->printTree(pNode);
		}
	cout << endl << endl;
	pTree->printFrequencies();
}

Analyzer::Analyzer(AnalyzeCommand* inCommand) : Analyzer() { pCommand = inCommand; }
Analyzer::Analyzer() { pTree = new Tree(); }
