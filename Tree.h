#pragma once
#include <map>
#include <vector>
#include <string>
#include "Node.h"

class Tree {
private:
	std::map<std::string, Node*>* mNodes;
	std::vector<bool> vIsVisited;
    
    void printNode(Node* inNode, int inLevel);
public:
	Node* getNode(std::string inPath);
	
    Node* addNewNode(const std::string& inFileName, const std::string& inFilePath);
	void addNodeToParent(Node* inParent, Node* inNode); 

	bool isVisited(Node* inNode);
	void setIsVisited(Node* inNode);
	void resetVisited();

	void updateFrequencies(Node* inNode);

	void printTree(Node* inNode);
	void printFrequencies();
	Tree();
	~Tree();
};