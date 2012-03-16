#include "xmlElement.h"
#include <list>
#include <typeinfo>

using namespace std;	


xmlElement::xmlElement(string elName)
{
	name = elName;
	parentElement = NULL;
	childElementCount = 0;
}

xmlElement::~xmlElement()
{
}

string xmlElement::getName()
{
	return name;
}

vector<attribute*> xmlElement::getAllAttributes()
{
	return att;
}
	
attribute * xmlElement::getAttribute(int i)
{
	return att[i];
}


int xmlElement::getChildElementCount()
{
	return childElementCount;
}

vector<xmlNode*> xmlElement::getAllChildNode()
{	
	return childNode;
}
	
xmlNode* xmlElement::getChildNode(int i)
{
	return childNode[i];
}

vector<xmlElement*> xmlElement::getAllChildElement()
{
	return childElement;
}

xmlElement* xmlElement::getChildElement(int i)
{
	return childElement[i];
}

	
xmlElement * xmlElement::getParent()
{
	return parentElement;
}

void xmlElement::setParent(xmlElement * elParent)
{
	parentElement = elParent;
}

void xmlElement::addAttribute(attribute* elAtt)
{
	att.push_back(elAtt);
}

void xmlElement::addXmlNode(xmlNode * elNode)
{
	childNode.push_back(elNode);
	xmlElement * elElement = dynamic_cast<xmlElement*>(elNode);
	if (elElement != 0)
	{
		childElement.push_back(elElement);
		childElementCount++;
		elElement->setParent(this);
	}
}

