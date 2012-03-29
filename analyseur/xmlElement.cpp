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
	xmlElement * elElement = dynamic_cast<xmlElement*>(elNode);
	if (elElement != 0)
	{
		childElement.push_back(elElement);
		childElementCount++;
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
			cout << "==============\n\n=========" << childElement[i]->getFullName() << endl;
			if (result != NULL)
				return result;
		}
	}
	return NULL;
}


xmlElement * xmlElement::copy ()
{
	cout << "XML ELEMENT COPY 1!!!" << endl;
	xmlElement * newEltResult;
	cout << name << endl;
	if (ns == "")
		newEltResult = new xmlElement(name);
	else 
		newEltResult = new xmlElement(name,ns);
	cout << "XML ELEMENT COPY 2!!" << endl;
	for (int i = 0 ; i < childNode.size() ; i++)
	{
		cout << "XML ELEMENT COPY 3!!" << endl;
		xmlNode * tempChild = childNode[i];
		xmlElement * tempElement =  dynamic_cast<xmlElement*>(tempChild);
		cout << "XML ELEMENT COPY 4!!" << endl;
		if(tempElement != NULL)
		{
			cout << "XML ELEMENT COPY 5!!" << endl;
			newEltResult->addXmlNode(tempElement->copy());
		}	
		else
		{
			cout << "XML ELEMENT COPY 6!!" << endl;	
			xmlText * tempText =  new xmlText(((xmlText*)tempChild)->getText());
			newEltResult->addXmlNode(tempText);
		}
	}
	cout << "XML ELEMENT COPY !!!" << endl;
	newEltResult->display();
	cout << "END XML ELEMENT COPY !!!" << endl;
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
