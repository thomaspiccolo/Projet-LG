#include "xmlElement.h"

using namespace std;	


xmlElement::xmlElement(string name, xmlElement * owner, xmlElement * parentElement)
{
}

xmlElement::~xmlElement()
{
}

string xmlElement::getName()
{
	return name;
}

list<attribute> xmlElement::getAllAttributes()
{
	return att;
}
	
attribute * xmlElement::getAttribute(int i)
{
}

int xmlElement::getChildElementCount()
{
	return childElementCount;
}

list<xmlNode*> xmlElement::getAllChildNode()
{	
	return childNode;
}
	
xmlNode* xmlElement::getChildNode(int i)
{
}

list<xmlElement*> xmlElement::getAllChildElement()
{
	return childElement;
}

xmlElement* xmlElement::getChildElement(int i)
{
}

xmlElement * xmlElement::getOwner()
{
	return owner;
}
	
xmlElement * xmlElement::getParent()
{
	return parentElement;
}

void xmlElement::addAttribute(attribute att)
{
}

void xmlElement::addXmlNode(xmlNode * node)
{
}

