#include "xmlTransform.h"
#include <string>


void find (xmlElement* elNode,  xmlElement* xslRoot)
{
	bool find = false;
	int i = 0 ;
	xmlElement* elCurrent;
	while ((i < xslRoot->getChildElementCount())||(find == false))
	{
		elCurrent = xslRoot->getChildElement(i);
		if (elCurrent->getFullName() == "xsl:template")
		{	
			attribute * currentAtt;
			int attCount = elCurrent->getAttributeCount();
			for (int j = 0 ; j < attCount ; j++)
			{
				currentAtt = elCurrent->getAttribute(j);
				cout << (currentAtt->id == "match") << "=" << (currentAtt->value == elNode->getName()) << endl;		
				if ((currentAtt->id == "match") && (currentAtt->value == elNode->getName()))
				{
					//transform(elNode,elCurrent);
					xmlElement* temp = elCurrent;
					xmlElement* elNodeParent = elNode->getParent();
					int i = 0;
					if (elNodeParent != NULL)
					{
						temp = temp->getElementByFullName("xsl:apply-templates");
						if (temp != NULL)
								cout << "Apply-Temlates find for : " << temp->getName() << endl;
						else
							cout << "Apply-Temlates not find for : " << endl; // << temp->getName() << endl;
					}
					find = true;
				}
			}
		}
		i++;	
	}
}

void transform (xmlElement*& elNode, xmlElement* elNewParent)
{
	xmlElement* temp = elNewParent;
	xmlElement* elNodeParent = elNode->getParent();
	int i = 0;
	if (elNodeParent != NULL)
	{
	}
		
}
