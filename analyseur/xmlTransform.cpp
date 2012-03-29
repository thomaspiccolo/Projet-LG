#include "xmlTransform.h"
#include <string>


xmlElement * find (xmlElement* elNode,  xmlElement* xslRoot)
{
	bool find = false;
	int i = 0 ;
	xmlElement* elCurrent;
	xmlElement * elXSLTemplateCpy;

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
				if ((currentAtt->id == "match") && (currentAtt->value == elNode->getName()))
				{
					elXSLTemplateCpy = elCurrent->copy();
					xmlElement* elApplyTemplates = elXSLTemplateCpy->getElementByFullName("xsl:apply-templates");
					int i = 0;
					if (elApplyTemplates!= NULL)
					{
							transform(elNode,elXSLTemplateCpy,elApplyTemplates );
							find = true;
							return elXSLTemplateCpy;
					}					
				}
			}
		}
		i++;	
	}
}


void transform (xmlElement*& elXMLNode, xmlElement * elXSLTemplate , xmlElement* elApplyTemplates)
{
	int itNode = 0;
	int itElement = 0;
	bool find = false;
	
	elXMLNode->setParent(elApplyTemplates->getParent());
	xmlElement * elATParent = elApplyTemplates->getParent(); //elATParent = elApplyTemplatesParent

	while (find == false && itNode < elATParent->getAllChildNode().size())
	{
		if (elATParent->getChildNode(itNode) == elApplyTemplates)
		{
			elATParent->getAllChildNodeVector()->at(itNode) = elXMLNode;
			find = true;
		}
		else
			itNode++;
	}
	find = false;
	while (find == false && itElement < elATParent->getAllChildElement().size())
	{
		if (elATParent->getChildElement(itElement) == elApplyTemplates)
		{
			elATParent->getAllChildElementVector()->at(itElement) = elXMLNode;
			find = true;
		}
		else
			itElement++;
	}	
}

