#pragma once
#include "Command.h"
#include "OptionManager.h"
#include "Tree.h"
#include <filesystem>

class AnalyzeCommand : public Command {
private:
	OptionManager* pOptionManager;
	Tree* pTree;

	void populateTree(const std::filesystem::path& inFile);
	std::filesystem::path getFilePath(const std::filesystem::path& inFile, const std::filesystem::path& inDirectory, bool isRelativePath);
	bool isFileExist(const std::filesystem::path& inFile, const std::filesystem::path& inDirectory);

	std::string readFile(const std::string& path);
public:
	virtual void validate();
	virtual void run();

	AnalyzeCommand();
	virtual ~AnalyzeCommand();
};