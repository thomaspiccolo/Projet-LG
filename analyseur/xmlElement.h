#ifndef XMLELEMENT_H
#define XMLELEMENT_H

#include <vector>
#include <string>
#include "xmlNode.h"

using namespace std;

typedef struct attribute{
	string id;
	string value;
};

class xmlElement : public xmlNode {
	private:
	string ns;
	string name;
	vector<attribute*> att;
	int childElementCount;
	vector<xmlNode*> childNode;
	vector<xmlElement*> childElement;
	xmlElement * parentElement;

	public:

	xmlElement(string name);
	xmlElement(string name, string ns);
	~xmlElement();
	
	string getName();
	string getNameSpace();
	string getFullName();
	vector<attribute*> getAllAttributes();
	attribute * getAttribute(int i);
	int getAttributeCount();
	int getChildElementCount();
	vector<xmlNode*> getAllChildNode();
	vector<xmlNode*> * getAllChildNodeVector();
	xmlNode* getChildNode(int i);
	vector<xmlElement*> getAllChildElement();
	vector<xmlElement*> * getAllChildElementVector();
	xmlElement * getChildElement(int i);
	xmlElement * getParent();

	void setParent(xmlElement * elParent);

	void addAttribute(attribute * elAtt);
	void addXmlNode(xmlNode * elNode);
	xmlElement * getElementByName(string name);
	xmlElement * getElementByFullName(string elName);
	xmlElement * copy ();
	void display();
};

#endif
