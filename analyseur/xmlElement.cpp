#include "xmlElement.h"
#include "xmlText.h"
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

string xmlElement::getNameSpace()
{
	return ns;
}

string xmlElement::getFullName()
{
	return ns+":"+name;
}

vector<attribute*> xmlElement::getAllAttributes()
{
	return att;
}
	
attribute * xmlElement::getAttribute(int i)
{
	return att[i];
}

int xmlElement::getAttributeCount()
{
	return att.size();
}


int xmlElement::getChildElementCount()
{
	return childElementCount;
}

int xmlElement::getChildNodeCount()
{
	return childNodeCount;
}

vector<xmlNode*> xmlElement::getAllChildNode()
{	
	return childNode;
}

vector<xmlNode*> * xmlElement::getAllChildNodeVector()
{	
	return &childNode;
}
	
xmlNode* xmlElement::getChildNode(int i)
{
	return childNode[i];
}

vector<xmlElement*> xmlElement::getAllChildElement()
{
	return childElement;
}

vector<xmlElement*> * xmlElement::getAllChildElementVector()
{	
	return &childElement;
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
	childNodeCount++;
	xmlElement * elElement = dynamic_cast<xmlElement*>(elNode);
	if (elElement != 0)
	{
		childElement.push_back(elElement);
		childElementCount++;
		elElement->setParent(this);
	}
}

void xmlElement::removeXmlNode()
{
	xmlElement * elElement = dynamic_cast<xmlElement*>(childNode[childNode.size()-1]);
	childNode.pop_back();
	childNodeCount--;
	if (elElement != 0)
	{
		childElement.pop_back();
		childElementCount--;
		elElement->setParent(this);
	}
}

xmlElement * xmlElement::getElementByName(string elName)
{
	for(int i = 0; i < childElementCount; i++)
	{
		if (childElement[i]->name == elName)
		{
			return childElement[i];
		}
		else
		{
			xmlElement* result = getElementByName(name);
			if (result != NULL)
				return result;
		}
	}
	return NULL;
}

xmlElement * xmlElement::getElementByFullName(string elName)
{
	for(int i = 0; i < childElementCount; i++)
	{
		if (childElement[i]->getFullName() == elName)
		{
			return childElement[i];
		}
		else
		{
			xmlElement* result = childElement[i]->getElementByFullName(elName);
			if (result != NULL)
				return result;
		}
	}
	return NULL;
}


xmlElement * xmlElement::copy ()
{
	xmlElement * newEltResult;
	if (ns == "")
		newEltResult = new xmlElement(name);
	else 
		newEltResult = new xmlElement(name,ns);
	for (int i = 0 ; i < childNode.size() ; i++)
	{
		xmlNode * tempChild = childNode[i];
		xmlElement * tempElement =  dynamic_cast<xmlElement*>(tempChild);
		if(tempElement != NULL)
		{
			newEltResult->addXmlNode(tempElement->copy());
		}	
		else
		{
			xmlText * tempText =  new xmlText(((xmlText*)tempChild)->getText());
			newEltResult->addXmlNode(tempText);
		}
	}
	return newEltResult;
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
