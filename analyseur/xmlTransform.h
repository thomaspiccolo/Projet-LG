#ifndef XMLTRANSFORM_H
#define XMLTRANSFORM_H

#include <string>
#include <iostream>
#include "xmlElement.h"
#include "xmlText.h"

using namespace std;

//Cherche si l'élement à un template
xmlElement * find(xmlElement* elNode, xmlElement* xslRoot);

//Applique le template à elXMLNode
void transform (xmlElement*& elXMLNode , xmlElement* elApplyTemplates, xmlElement * xslRoot);

#endif