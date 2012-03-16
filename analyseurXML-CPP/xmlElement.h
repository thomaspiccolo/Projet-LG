#ifndef XMLELEMENT_H
#define XMLEMENT_H

#include <list>
#include <string>
#include "xmlNode.h"

using namespace std;

typedef struct attribute{
	string id;
	string value;
};

class xmlElement : public xmlNode {
	private:
	
	string name;
	list<attribute> att;
	int childElementCount;
	list<xmlNode*> childNode;
	list<xmlElement*> childElement;
	xmlElement * owner;
	xmlElement * parentElement;

	public:

	xmlElement(string name, xmlElement * owner, xmlElement * parentElement);
	~xmlElement();
	
	string getName();
	list<attribute> getAllAttributes();
	attribute * getAttribute(int i);
	int getChildElementCount();
	list<xmlNode*> getAllChildNode();
	xmlNode* getChildNode(int i);
	list<xmlElement*> getAllChildElement();
	xmlElement * getChildElement(int i);
	xmlElement * getOwner();
	xmlElement * getParent();

	void addAttribute(attribute att);
	void addXmlNode(xmlNode * node);

};

#endif
