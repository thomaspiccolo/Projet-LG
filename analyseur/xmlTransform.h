#include <string>
#include <iostream>
#include "xmlNode.h"
#include "xmlElement.h"

using namespace std;

void find(xmlElement* elNode, xmlElement* xslRoot);

void tranform(xmlElement* &elNode, xmlElement* elNewParent);
