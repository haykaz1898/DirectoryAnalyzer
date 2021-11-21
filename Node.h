#pragma once
#include <vector>
#include <string>

class Node {
private:
	static int iStaticId;
	int iId;
	std::string sPath;
	std::string sFileName;
	bool bFileExists;
	int iFrequency;
	std::vector<Node*>* vChidlren;
public:
	int getId();
	std::string getPath();
	void setPath(std::string inPath);

	std::string getFileName();
	void setFileName(std::string inFileName);

	bool isFileExist();
	void setFileExist(bool inIsExist);

	void addChidren(Node* inNode);
	std::vector<Node*>* getChildren();

	int getFrequency();
	void setFrequency(int inFrequency);
	void increaseFrequency(int inCount);

	Node(std::string inPath, std::string sFileName);
	Node();
	~Node();
};