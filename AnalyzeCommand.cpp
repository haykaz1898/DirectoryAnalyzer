#include "AnalyzeCommand.h"
#include <stack>
#include <sstream>
#include <fstream>
#include <iostream>
#include "InvalidDirectoryException.h"
#include "InvalidOptionException.h"
#include "CPPFileParser.h"
using namespace std;
using namespace filesystem;

void AnalyzeCommand::populateTree(const path& inFilePath) {
	stack<path> oStack;
	oStack.push(inFilePath);
	vector<bool> isVisited;
	path sCurrentDirectory;
	while (!oStack.empty()) {
		Node* pCurrentNode = pTree->getNode(oStack.top().generic_string());
		oStack.pop();
		sCurrentDirectory = path(pCurrentNode->getPath()).parent_path();
		pTree->setIsVisited(pCurrentNode);
		
		auto lines = CPPFileParser::getLines(readFile(pCurrentNode->getPath()));
		int iCursorPosition = 0;
		for (auto line : lines) {
			bool bFileExist = false;
			string sFileName = CPPFileParser::parseFileName(line);
			path file = path(sFileName);
			auto filePath = getFilePath(file, sCurrentDirectory, line.find("\"") != string::npos);

			if (filePath != "") {
				bFileExist = true;
				sCurrentDirectory = filePath.parent_path();
			}
			
			auto node = pTree->addNewNode(file.filename().generic_string(), (filePath == "" ? (sCurrentDirectory / file) : filePath).generic_string());
			pTree->addNodeToParent(pCurrentNode, node);
			if (!pTree->isVisited(node)) {
				node->increaseFrequency(1);
				if (bFileExist) {
					node->setFileExist(bFileExist);
					oStack.push(filePath);
				}
			}
			else
				pTree->updateFrequencies(node);
		}
	}
}

path AnalyzeCommand::getFilePath(const path& inFile, const path& inDirectory, bool isRelativePath) {
	vector<path> paths;
	path oFoundedFilePath;
	if (isRelativePath)
		paths.push_back((inDirectory / inFile));
	else {
		auto vOptionArgs = getOptionArguments();
		if (vOptionArgs->begin() != vOptionArgs->end())
			for (auto sPath : *(*vOptionArgs->begin()).second)
				paths.push_back((path(sPath) / inFile));
	}
	for (auto entry : paths) {
		if (isFileExist(entry.filename(), entry.parent_path()))
			oFoundedFilePath = entry;
	}
	return oFoundedFilePath;
}

bool AnalyzeCommand::isFileExist(const path& inFile,const path& inDirectory) {
	if (exists(inDirectory))
		for (auto& entry : directory_iterator(inDirectory))
			if (entry.path().filename() == inFile)
				return true;
	return false;
}

string AnalyzeCommand::readFile(const string& path) {
	ifstream file(path);
	string result;
	return result.assign(istreambuf_iterator<char>(file), istreambuf_iterator<char>());
}

void AnalyzeCommand::run() {
	validate();
	stack<string> oDirectories;
	oDirectories.push(getCommandArguments()->front());
	while (!oDirectories.empty()) {
		string sDirectory = oDirectories.top();
		oDirectories.pop();
		for (auto & entry : directory_iterator(sDirectory))
			if (entry.path().extension() == ".cpp") {
				auto pNode = pTree->addNewNode(entry.path().filename().generic_string(), entry.path().generic_string());
				pNode->setFileExist(true);
				populateTree(entry.path());
				pTree->printTree(pNode);
			}
			else if (entry.is_directory()) {
				oDirectories.push(entry.path().generic_string());
			}
	}
	cout << endl << endl;
	pTree->printFrequencies();
}

void AnalyzeCommand::validate() {
	for (auto directory : *vCommandArguments)
		if (!is_directory(directory))
			throw InvalidDirectoryException("Analyze", directory);

	for (auto option : *mOptionArguments) {
		Option* pOption = pOptionManager->getOptionByName(option.first);
		if (pOptionManager && pOptionManager->checkOptionArguments(pOption, *option.second)) {
			for (auto directory : *option.second)
				if (!is_directory(directory))
					throw InvalidDirectoryException("Analyze", directory);
		}
		else
			throw InvalidOptionException("Analyze", option.first);
	}
}

AnalyzeCommand::AnalyzeCommand() {
	pTree = new Tree();
	pOptionManager = new OptionManager("Analyze");
	pOptionManager->addNewOption("-I", "", "Sources search path", ArgumentType::OPTIONAL, false);
}
AnalyzeCommand::~AnalyzeCommand() {
	delete pTree;
	delete pOptionManager;
}