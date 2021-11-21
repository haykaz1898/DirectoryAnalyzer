#include "Tree.h"
#include "Node.h"
#include <stack>
#include <iostream>
#include <algorithm>
using namespace std;

Node* Tree::getNode(string inPath) { 
	auto node = mNodes->find(inPath);
	return node != mNodes->end() ? (*node).second : nullptr;
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
	if (getNode(inParent->getPath()) && getNode(inNode->getPath()))
		inParent->addChidren(inNode);
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
	vector<bool> visited(mNodes->size(), false);
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
		if (!visited[pCurrentNode->getId()]) {
			printNode(pCurrentNode, iLevel);
			iLevel++;
		}				
		if (pCurrentNode->getChildren()->size() == 0 || visited[pCurrentNode->getId()]) {
			visited[pCurrentNode->getId()] = false;
			oNodes.pop();
			iLevel--;
		}
		else {
			visited[pCurrentNode->getId()] = true;	
			for (auto node : *pCurrentNode->getChildren())
				if (!visited[node->getId()])
					oNodes.push(node);
				else
					isCycle = true;
		}
	}
}

void Tree::printFrequencies() {
	vector<pair<int, string>> frequencies;
	for (auto entry : *mNodes)
		frequencies.push_back(make_pair(entry.second->getFrequency(), entry.second->getFileName()));
		sort(frequencies.begin(), frequencies.end(), [](pair<int, string> a, pair<int, string> b) {
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

Tree::Tree() {
	mNodes = new map<string,Node*>();
}
Tree::~Tree() {
	for (auto entry : *mNodes)
		delete entry.second;	
	delete mNodes;
}
