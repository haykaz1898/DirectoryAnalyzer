#include "Option.h"
using namespace std;

string Option::getShortName() { return sShortName; }
string Option::getLongName() { return sLongName; }
string Option::getDescription() { return sDescription; }
ArgumentType Option::getOptionType() { return eArgumentType; }
bool Option::isSingleArg() { return bIsSingleArg; }
string Option::toString() { return ""; } //TODO realize ToStringMethod
Option::Option(string inShortName, string inLongName, string inDescription, ArgumentType inArgumentType, bool inIsSingleArg) {
	sShortName = inShortName;
	sLongName = inLongName;
	sDescription = inDescription;
	eArgumentType = inArgumentType;
	bIsSingleArg = inIsSingleArg;
}