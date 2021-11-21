#pragma one
#include "AnalyzeCommand.h"
#include "Tree.h"
#include <string>
class Analyzer {
private:
	AnalyzeCommand* pCommand;
	Tree* pTree;

	void populateTree(std::string inFile);
	std::string getFilePath(std::string inFileName, bool isRelativePath);
	std::string parseFileName(std::string& inLine);
	std::string readFile(std::string path);
public:
	void Analyze();
	
	Analyzer(AnalyzeCommand* inCommand);
	Analyzer();
};