#include "xmlTransform.h"
#include <string>


xmlElement * find (xmlElement* elNode,  xmlElement* xslRoot)
{
	bool find = false;
	int i = 0 ;
	xmlElement* elCurrent;
	xmlElement * elXSLTemplateCpy;
	
	
	cout << "++++++++++++++++++++++++++++++++++++++find" << endl;
	elNode->display();
	cout << "/++++++++++++++++++++++++++++++++++++++find" << endl;

	while ((i < xslRoot->getChildElementCount())&&(find == false))
	{
	cout << "+++++++++++++++++++++++++1++++++++++++find" << i << endl<<xslRoot->getChildElementCount() <<endl;
		elCurrent = xslRoot->getChildElement(i);
		if (elCurrent->getFullName() == "xsl:template")
		{	
	cout << "+++++++++++++++++++++++++2++++++++++++find" << endl;
			attribute * currentAtt;
			int attCount = elCurrent->getAttributeCount();
			for (int j = 0 ; j < attCount ; j++)
			{
	cout << "+++++++++++++++++++++++++3++++++++++++find" << endl;
				currentAtt = elCurrent->getAttribute(j);
				if ((currentAtt->id == "match") && (currentAtt->value == elNode->getName()))
				{
	cout << "+++++++++++++++++++++++++4++++++++++++find" << endl;
					elXSLTemplateCpy = elCurrent->copy();
					xmlElement* elApplyTemplates = elXSLTemplateCpy->getElementByFullName("xsl:apply-templates");
					if (elApplyTemplates!= NULL)
					{
	cout << "+++++++++++++++++Transform++++++++++++++find" << endl;
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
	
	cout << "======TransformIn==" <<  endl ;

	elXMLNode->setParent(elApplyTemplates->getParent());
	xmlElement * elATParent = elApplyTemplates->getParent(); //elATParent = elApplyTemplatesParent
	cout << "======TransformIn==" <<  endl ;

	/* TO DO : Modifier les insertion pour supprimer les noeux applytemplate et rapport par l'utilisation de insert de vector
	*/
	while (ATfind == false && itNode < elATParent->getAllChildNode().size())
	{
	cout << "======TransformIn==1" <<  endl ;
		if (elATParent->getChildNode(itNode) == elApplyTemplates)
		{
				cout << "======TransformIn=2" <<  endl ;

			int size = elXMLNode->getChildNodeCount();
			vector<xmlNode*> tempVector;
			while (elATParent->getChildNode(elATParent->getAllChildNode().size()-1) != elApplyTemplates )
			{
					cout << "======TransformIn=3" <<  endl ;

				if (dynamic_cast<xmlElement*>(elATParent->getChildNode(elATParent->getAllChildNode().size()-1)))
				{	
					cout << "======TransformIn=4" <<  endl ;
					cout << (elApplyTemplates==elATParent->getChildNode(elATParent->getAllChildNode().size()-1))<< endl;
//					elATParent->getChildNode(elATParent->getAllChildNode().size()-1)->display();
					xmlElement * temp = ((xmlElement*)elATParent->getChildNode(elATParent->getAllChildNode().size()-1))->copy();
					cout << "======TransformIn=4" <<  endl ;
					elATParent->removeXmlNode();
					cout << "======TransformIn=4" <<  endl ;
					tempVector.push_back(temp);
					cout << "======TransformIn=4" <<  endl ;
				}
				else
				{
					cout << "======TransformIn=5" <<  endl ;
					xmlText* temp = new xmlText(((xmlText*)elATParent->getChildNode(elATParent->getAllChildNode().size()-1))->getText());
					tempVector.push_back(temp);
					elATParent->removeXmlNode();

				}						
			}
			cout << "======TransformIn=22" <<  endl ;

			elATParent->removeXmlNode(); // On retire le ApplyTemplates
			cout << "======TransformIn=22" <<  endl ;
			for (int i = 0 ; i <  size ; i++)
			{
				cout << "===============" <<  i ;
				if (dynamic_cast<xmlElement*>(elXMLNode->getChildNode(i)))
				{
					cout << "============Element"  << endl;				
					xmlElement * temp = ((xmlElement*)elXMLNode->getChildNode(i))->copy();
					temp = find(temp,xslRoot);
					cout << "Test" << endl;
					if ( temp != NULL )
						elATParent->addXmlNode(temp);
					elATParent->display();
				}
				else
				{
					xmlText * temp = new xmlText(((xmlText*)(elXMLNode->getChildNode(i)))->getText());
					cout << "============Text"  << endl << temp->getText() << endl ;				
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

