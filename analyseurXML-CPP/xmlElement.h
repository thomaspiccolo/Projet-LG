#ifndef XMLELEMENT_H
#define XMLEMENT_H

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
	vector<attribute*> getAllAttributes();
	attribute * getAttribute(int i);
	int getChildElementCount();
	vector<xmlNode*> getAllChildNode();
	xmlNode* getChildNode(int i);
	vector<xmlElement*> getAllChildElement();
	xmlElement * getChildElement(int i);
	xmlElement * getParent();

	void setParent(xmlElement * elParent);

	void addAttribute(attribute * elAtt);
	void addXmlNode(xmlNode * elNode);
	void display();
};

#endif
