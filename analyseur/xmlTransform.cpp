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
	vector<xmlNode*>::iterator itNode;
	vector<xmlElement*>::iterator itElement ;
	bool find = false;
	
	
	elXMLNode->setParent(elApplyTemplates->getParent());
	xmlElement * elATParent = elApplyTemplates->getParent(); //elATParent = elApplyTemplatesParent
	itNode =  elATParent->getAllChildNode().begin();
	itElement = elATParent->getAllChildElement().begin();

	/* TO DO : Modifier les insertion pour supprimer les noeux applytemplate et rapport par l'utilisation de insert de vector
	*/
	while (find == false && itNode != elATParent->getAllChildNode().end())
	{
		if (*itNode == elApplyTemplates)
		{
			cout << "Trace" << ((xmlElement*)(*itNode))->getFullName() << endl;
			elATParent->getAllChildNodeVector()->insert(itNode,elXMLNode->getAllChildNodeVector()->begin(),elXMLNode->getAllChildNodeVector()->end());
			find = true;
		}
		else
			++itNode;
	}
	find = false;
/*	while (find == false && itElement < elATParent->getAllChildElement().end())
	{
		if (elATParent->getChildElement(itElement) == elApplyTemplates)
		{
			elATParent->getAllChildElementVector()->at(itElement) = elXMLNode;
			find = true;
		}
		else
			++itElement;
	}	*/
	elATParent->display();
	elXMLNode->display();
}

