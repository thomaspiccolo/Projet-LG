#include "xmlTransform.h"
#include <string>


xmlElement * find (xmlElement* elNode,  xmlElement* xslRoot)
{
	bool find = false;
	int i = 0 ;
	xmlElement* elCurrent;
	xmlElement * elXSLTemplateCpy;

	while ((i < xslRoot->getChildElementCount())&&(find == false))
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
							transform(elNode,elXSLTemplateCpy,elApplyTemplates, xslRoot );
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


void transform (xmlElement*& elXMLNode, xmlElement * elXSLTemplate , xmlElement* elApplyTemplates, xmlElement *xslRoot)
{
	int itNode = 0;
	bool ATfind = false;
	
	
	elXMLNode->setParent(elApplyTemplates->getParent());
	xmlElement * elATParent = elApplyTemplates->getParent(); //elATParent = elApplyTemplatesParent
	
	while (ATfind == false && itNode < elATParent->getAllChildNode().size())
	{
		if (elATParent->getChildNode(itNode) == elApplyTemplates)
		{
			int size = elXMLNode->getChildNodeCount();
			vector<xmlNode*> tempVector;
			while (elATParent->getChildNode(elATParent->getAllChildNode().size()-1) != elApplyTemplates )
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
				if (dynamic_cast<xmlElement*>(elXMLNode->getChildNode(i)))
				{
					xmlElement * temp = ((xmlElement*)elXMLNode->getChildNode(i))->copy();
					temp = find(temp,xslRoot);
					if ( temp != NULL )
					{
						for (int j = 0 ; j < temp->getChildNodeCount() ; j++)
							elATParent->addXmlNode(temp->getChildNode(j));
					}
				}
				else
				{
					xmlText * temp = new xmlText(((xmlText*)(elXMLNode->getChildNode(i)))->getText());
					elATParent->addXmlNode(temp);
				}
				
			}
			for (int i = 0 ; i < tempVector.size() ; i++ )
			{
				elATParent->addXmlNode(tempVector[i]);
			}
			ATfind = true;
		}
		else
			itNode++;
	}
	ATfind = false;
}

