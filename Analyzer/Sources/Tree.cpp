#include "Tree.h"
#include "Node.h"
#include <stack>
#include <iostream>
#include <algorithm>
using namespace std;

Node* Tree::getNode(string inPath) { 
	auto itNode = mNodes->find(inPath);
	return itNode != mNodes->end() ? (*itNode).second : nullptr;
}

Node* Tree::addNewNode(const std::string& inFileName, const std::string& inFilePath) {
	Node* pNode = getNode(inFilePath);
	if (!pNode) {
		pNode = new Node(inFilePath, inFileName);
		mNodes->insert(make_pair(inFilePath, pNode));
		vIsVisited.push_back(false);
	}
	return pNode;
}

void Tree::addNodeToParent(Node* inParent, Node* inNode) {
	if (inParent && inNode && getNode(inParent->getPath()) && getNode(inNode->getPath())) {
		bool bHasAlready = false;
		for (auto entry : *(inParent->getChildren()))
			if (entry == inNode)
				bHasAlready = true;
		if (!bHasAlready)
			inParent->addChidren(inNode);
	}
}

bool Tree::isVisited(Node* inNode) { return vIsVisited[inNode->getId()]; }
void Tree::setIsVisited(Node* inNode) { vIsVisited[inNode->getId()] = true; }
void Tree::resetVisited() {
	for (auto entry : vIsVisited)
		entry = false;
}

void Tree::updateFrequencies(Node* inNode) {
	stack<Node*> oNodes;
	vector<bool> isVisited(mNodes->size(), false);
	oNodes.push(inNode);
	while(!oNodes.empty()) {
		Node* pCurrent = oNodes.top();
		pCurrent->increaseFrequency(1);
		isVisited[pCurrent->getId()] = true;
		oNodes.pop();
		for (auto child : *pCurrent->getChildren())
			if (!isVisited[child->getId()])
				oNodes.push(child);
	}
}

void Tree::printNode(Node* inNode, int inLevel) {
	string sToPrint = "\n";
	for (int i = 0; i < inLevel * 2; i++)
		sToPrint += '.';
	sToPrint += inNode->getFileName() + (!inNode->isFileExist() ? " (!) " : "");
	cout << sToPrint;
}

void Tree::printTree(Node* inNode) {
	vector<bool> vVisited(mNodes->size(), false);
	stack<Node*> oNodes;
	oNodes.push(inNode);
	int iLevel = 0;
	bool isCycle = false;
	while (!oNodes.empty()){
		Node* pCurrentNode = oNodes.top();
		if (isCycle) {
			cout << " (Cycle detected!) ";
			isCycle = false;
		}
		if (!vVisited[pCurrentNode->getId()]) {
			printNode(pCurrentNode, iLevel);
			iLevel++;
		}				
		if (pCurrentNode->getChildren()->size() == 0 || vVisited[pCurrentNode->getId()]) {
			vVisited[pCurrentNode->getId()] = false;
			oNodes.pop();
			iLevel--;
		}
		else {
			vVisited[pCurrentNode->getId()] = true;	
			for (auto node : *pCurrentNode->getChildren())
				if (!vVisited[node->getId()])
					oNodes.push(node);
				else
					isCycle = true;
		}
	}
}

void Tree::printFrequencies() {
	vector<pair<int, string>> vFrequencies;
	for (auto entry : *mNodes)
		vFrequencies.push_back(make_pair(entry.second->getFrequency(), entry.second->getFileName()));
		sort(vFrequencies.begin(), vFrequencies.end(), [](pair<int, string> a, pair<int, string> b) {
		if (a.first > b.first)
			return true;
		else if (a.first == b.first && a.second < b.second)
			return true;
		else 
			return false;
	});
	for (auto entry : vFrequencies)
		cout << entry.second << " " << entry.first << "\n";
}

Tree::Tree() {
	mNodes = new map<string,Node*>();
}
Tree::~Tree() {
	for (auto entry : *mNodes)
		delete entry.second;	
	delete mNodes;
}
