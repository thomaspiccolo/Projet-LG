#include "xmlTransform.h"
#include <list>


void find (xmlElement* elNode,  xmlElement* xslRoot)
{
	bool find = false;
	int i = 0 ;
	xmlElement* elCurrent;
	while ((i < xslRoot->getChildElementCount())||(find = false))
	{
		elCurrent = xslRoot->getChildElement(i);
		if (elCurrent->getFullName() == "xsl:template")
		{	
			attribute * currentAtt;
			int attCount = elCurrent->getAttributeCount();
			for (int j = 0 ; j < attCount ; j++)
			{
				currentAtt = elCurrent->getAttribute(j);
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
							printf("%s", temp->getName());
						else
							printf("Not find");
					}
					find = true;
				}
			}
		}	
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
