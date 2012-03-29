#ifndef XMLTRANSFORM_H
#define XMLTRANSFORM_H

#include <string>
#include <iostream>
#include "xmlElement.h"
#include "xmlText.h"

using namespace std;

xmlElement * find(xmlElement* elNode, xmlElement* xslRoot);

void transform (xmlElement*& elXMLNode, xmlElement * elXSLTemplate , xmlElement* elApplyTemplates);

#endif