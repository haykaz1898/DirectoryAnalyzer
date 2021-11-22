#pragma once
#include <vector>
#include <string>
class CPPFileParser {
private:
	static std::vector<std::pair<int, int>> getCommentPositions(const std::string& inFile);
	static bool isCommentedLine(int inLineCursor, std::vector<std::pair<int, int>>& inCommentPositions);
public:
	static std::vector<std::string> getLines(const std::string& inFile);
};