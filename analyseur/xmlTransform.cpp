#include "xmlTransform.h"
#include <string>


xmlElement * find (xmlElement* elNode,  xmlElement* xslRoot)
{
	//Initialisation des variables
	int i = 0 ;
	xmlElement* elCurrent;
	xmlElement * elXSLTemplateCpy;

	// Tant que l'on a pas parcouru tout les element du xsl ou que l'on n'a pas trouver le template
	while ((i < xslRoot->getChildElementCount()))
	{
		//Mise à jour du pointeur courant sur l'element enfant i
		elCurrent = xslRoot->getChildElement(i);
		//Si l'element enfant i est bien 'xsl:template'
		if (elCurrent->getFullName() == "xsl:template")
		{	
			//Recherche dans le noeud s'il match le noeud XML
			attribute * currentAtt;
			int attCount = elCurrent->getAttributeCount();
			for (int j = 0 ; j < attCount ; j++)//Parcours des attributs du noeud xsl
			{
				currentAtt = elCurrent->getAttribute(j);
				if ((currentAtt->id == "match") && (currentAtt->value == elNode->getName()))//Si le match correspond
				{
					//On copy le noeud xslTemplate pour l'appliquer
					elXSLTemplateCpy = elCurrent->copy();
					//On cherche le apply-templates dans la copie
					xmlElement* elApplyTemplates = elXSLTemplateCpy->getElementByFullName("xsl:apply-templates");
					if (elApplyTemplates!= NULL)//S'il y a un apply-templates
					{
						//On applique la transformation de l'arbre
						transform(elNode,elApplyTemplates, xslRoot );
						//On renvoi le xslTemplate avec le apply template modifié
						return elXSLTemplateCpy;
					}					
				}
			}
		}
		i++;	
	}
	//S'il n'y a pas de match qui correspond, on renvoi NULL.
	return NULL;
}


void transform (xmlElement*& elXMLNode, xmlElement* elApplyTemplates, xmlElement *xslRoot)
{
	//Initialisation des variables
	int itNode = 0;
	bool ATfind = false;
	
	//Modificiation du parent du noeud sur lequel appliquer le applytemplates
	elXMLNode->setParent(elApplyTemplates->getParent());
	xmlElement * elATParent = elApplyTemplates->getParent(); //elATParent = elApplyTemplatesParent
	
	//Tant que l'on n'a pas trouver l'applytemplate et que l'on a pas parcouru tout les noeud frere de applytemplates
	while (ATfind == false && itNode < elATParent->getAllChildNode().size())
	{
		if (elATParent->getChildNode(itNode) == elApplyTemplates)//Si le noeud 'frere' de applytemplate est applytemplate
		{
			//On va copier les noeud 'frere' qui se trouve après le applytemplates
			int size = elXMLNode->getChildNodeCount();
			vector<xmlNode*> tempVector;
			//Tant que l'on est après le applytemplate
			while (elATParent->getChildNode(elATParent->getAllChildNode().size()-1) != elApplyTemplates )
			{
				if (dynamic_cast<xmlElement*>(elATParent->getChildNode(elATParent->getAllChildNode().size()-1)))//Si le dernier est un xmlElement
				{	
					//On le copie
					xmlElement * temp = ((xmlElement*)elATParent->getChildNode(elATParent->getAllChildNode().size()-1))->copy();
					elATParent->removeXmlNode();
					//On le retire en tant que frere
					tempVector.push_back(temp);
				}
				else//Si le dernier est un xmlText
				{
					//On le copie
					xmlText* temp = new xmlText(((xmlText*)elATParent->getChildNode(elATParent->getAllChildNode().size()-1))->getText());
					tempVector.push_back(temp);
					//On le retire en tant que frère
					elATParent->removeXmlNode();

				}						
			}

			elATParent->removeXmlNode(); // On retire le ApplyTemplates
			for (int i = 0 ; i <  size ; i++)
			{
				if (dynamic_cast<xmlElement*>(elXMLNode->getChildNode(i)))//Si le nouveau frère est un xmlElement
				{
					//On en fait une copie
					xmlElement * temp = ((xmlElement*)elXMLNode->getChildNode(i))->copy();
					//On applique la recherche de xslTemplate sur ce noeud
					temp = find(temp,xslRoot);
					if ( temp != NULL )//S'il y a un template
					{
						//Pour chaque enfant du nouveau noeud avec le template appliqué
						for (int j = 0 ; j < temp->getChildNodeCount() ; j++)
							//On l'ajoute en tant que frere
							elATParent->addXmlNode(temp->getChildNode(j));
					}
				}
				else//Si c'est un xmlText
				{
					//On en fait une copie
					xmlText * temp = new xmlText(((xmlText*)(elXMLNode->getChildNode(i)))->getText());
					//On l'ajoute en tant que frere
					elATParent->addXmlNode(temp);
				}
				
			}
			//Pour tout les anciens frère que l'on avait sauvegarder
			for (int i = 0 ; i < tempVector.size() ; i++ )
			{
				//On les remets en tant que frere
				elATParent->addXmlNode(tempVector[i]);
			}
			//On indique que l'on a bien trouver un applytemplate et qu'il a été appliqué
			ATfind = true;
		}
		else//On avance 
			itNode++;
	}
}

