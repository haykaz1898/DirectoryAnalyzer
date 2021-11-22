#include "Node.h"
using namespace std;
int Node::iStaticId = 0;

int Node::getId() { return iId; }

string Node::getPath() { return sPath; }
void Node::setPath(string inPath) { sPath = inPath;}

string Node::getFileName() { return sFileName;}
void Node::setFileName(string inFileName) { sFileName = inFileName; }

bool Node::isFileExist() { return bFileExists; }
void Node::setFileExist(bool inIsExist) { bFileExists = inIsExist; }

void Node::addChidren(Node* inNode) { vChidlren->push_back(inNode);}
vector<Node*>* Node::getChildren() { return vChidlren; }

int Node::getFrequency() { return iFrequency; }
void Node::setFrequency(int inFrequency) { iFrequency = inFrequency; }
void Node::increaseFrequency(int inCount) { iFrequency += inCount; }

Node::Node(string inPath, string inFileName) : Node() {
    iId = iStaticId++;
	sPath = inPath;
	sFileName = inFileName;
}
Node::Node()  { vChidlren = new vector<Node*>(); }
Node::~Node() { delete vChidlren; }
