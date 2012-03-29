#ifndef XMLTRANSFORM_H
#define XMLTRANSFORM_H

#include <string>
#include <iostream>
#include "xmlElement.h"

using namespace std;

void find(xmlElement* elNode, xmlElement* xslRoot);

void tranform(xmlElement* &elNode, xmlElement* elNewParent);

#endif