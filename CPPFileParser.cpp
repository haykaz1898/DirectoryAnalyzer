#include "CPPFileParser.h"

using namespace std;
std::vector<std::pair<int, int>> CPPFileParser::getCommentPositions(const string& inFile) {
	vector<pair<int, int>> vResult;
	for (int i = 0; i < inFile.size(); i++) {
		if (i + 1 < inFile.size()) {
			if (inFile[i] == '/' && inFile[i + 1] == '/') {
				for (int j = i + 1; j < inFile.size(); j++)
					if (inFile[j] == '\n') {
						vResult.push_back(make_pair(i, j));
						i = j;
						break;
					}
			}
			else if (inFile[i] == '/' && inFile[i + 1] == '*') {
				for (int j = i + 1; j < inFile.size(); j++)
					if (j + 1 < inFile.size() && inFile[j] == '*' && inFile[j + 1] == '/') {
						vResult.push_back(make_pair(i, j));
						i = j;
						break;
					}
			}
		}
	}
	return vResult;
}

bool CPPFileParser::isCommentedLine(int inLineCursor, std::vector<std::pair<int, int>>& inCommentPositions) {
	for (auto entry : inCommentPositions)
		if (inLineCursor >= entry.first && inLineCursor <= entry.second)
			return true;
	return false;
}

std::vector<std::string> CPPFileParser::getLines(const string& inFile) {
	vector<string> lines;
	vector<pair<int, int>> commentPositions = getCommentPositions(inFile);

	for (int i = 0; i < inFile.size(); i++)
		if (inFile[i] == '#' && inFile.substr(i + 1, 7) == "include" && !isCommentedLine(i, commentPositions)) {
			string line = inFile.substr(i, 8);
			i += line.length() + 1;
			for (; i < inFile.size(); i++)
				if (inFile[i] != '\n' && inFile[i] != '#')
					line += inFile[i];
				else
					break;
			lines.push_back(line);
		}
	return lines;
}

string CPPFileParser::parseFileName(const string& inLine) {
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