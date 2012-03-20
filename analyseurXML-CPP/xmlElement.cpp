#include "xmlElement.h"
#include <list>
#include <typeinfo>
#include <iostream>

using namespace std;	


xmlElement::xmlElement(string elName)
{
	name = elName;
	ns = "";
	parentElement = NULL;
	childElementCount = 0;
}
xmlElement::xmlElement(string elName, string elNS)
{
	name = elName;
	ns = elNS;
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

void xmlElement::display()
{
	if (ns=="")
		cout << "<" << name ;
	else
		cout << "<" << ns << ":" << name ;
	if (att.size() > 0)
		for (int i = 0 ; i < att.size() ; i++)
			cout << " " << att[i]->id << "='" << att[i]->value << "'";
	if (childNode.size() == 0)
		cout << "/>" << endl;
	else
	{	
		cout << ">" << endl;
		for (int i = 0 ; i < childNode.size() ; i++)
			childNode[i]->display();
		if (ns=="")
			cout << "</" << name << ">" << endl;
		else
			cout << "</" << ns << ":" << name << ">" <<endl;
	}
}
