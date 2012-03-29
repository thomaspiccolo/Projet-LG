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
	return NULL;
}


void transform (xmlElement*& elXMLNode, xmlElement * elXSLTemplate , xmlElement* elApplyTemplates)
{
	int itNode = 0;
	bool find = false;
	
	
	elXMLNode->setParent(elApplyTemplates->getParent());
	xmlElement * elATParent = elApplyTemplates->getParent(); //elATParent = elApplyTemplatesParent

	/* TO DO : Modifier les insertion pour supprimer les noeux applytemplate et rapport par l'utilisation de insert de vector
	*/
	while (find == false && itNode < elATParent->getAllChildNode().size())
	{
		if (elATParent->getChildNode(itNode) == elApplyTemplates)
		{
			int size = elXMLNode->getChildNodeCount();
			vector<xmlNode*> tempVector;
			while (elATParent->getChildNode(elATParent->getAllChildNode().size()) != elApplyTemplates )
			{
				if (dynamic_cast<xmlElement*>(elATParent->getChildNode(elATParent->getAllChildNode().size()-1)))
				{	
					xmlElement * temp = ((xmlElement*)elATParent->getChildNode(elATParent->getAllChildNode().size()-1))->copy();
					elATParent->removeXmlNode();
					tempVector.push_back(temp);
				}
				else
				{
					xmlText* temp = new xmlText(((xmlText*)elATParent->getChildNode(elATParent->getAllChildNode().size()-1))->getText());
					tempVector.push_back(temp);
					elATParent->removeXmlNode();

				}						
			}
			elATParent->removeXmlNode(); // On retire le ApplyTemplates
			for (int i = 0 ; i <  size ; i++)
			{
				xmlNode* temp = ((xmlNode*)((xmlElement*)elXMLNode->getChildNode(i))->copy());
				elATParent->addXmlNode(temp);
			}
			for (int i = 0 ; i < tempVector.size() ; i++ )
			{
				elATParent->addXmlNode(tempVector[i]);
			}
			find = true;
		}
		else
			itNode++;
	}
	find = false;
}

