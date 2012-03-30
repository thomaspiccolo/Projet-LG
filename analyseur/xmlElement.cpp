#include "xmlElement.h"
#include "xmlText.h"
#include <list>
#include <typeinfo>
#include <iostream>
#include <string>

using namespace std;	

//Constructeurs
//Initialisation des variables
xmlElement::xmlElement(string elName)
{
	name = elName;
	ns = "";
	parentElement = NULL;
	childElementCount = 0;
}
xmlElement::xmlElement(string elName, string elNS)
{
	name = elName;
	ns = elNS;
	parentElement = NULL;
	childElementCount = 0;
}


//Desctructeur
xmlElement::~xmlElement()
{
}

//Getteur
string xmlElement::getName()
{
	return name;
}
string xmlElement::getNameSpace()
{
	return ns;
}
string xmlElement::getFullName()
{
	return ns+":"+name;
}
vector<attribute*> xmlElement::getAllAttributes()
{
	return att;
}	
attribute * xmlElement::getAttribute(int i)
{
	return att[i];
}
int xmlElement::getAttributeCount()
{
	return att.size();
}
int xmlElement::getChildElementCount()
{
	return childElementCount;
}
int xmlElement::getChildNodeCount()
{
	return childNodeCount;
}
vector<xmlNode*> xmlElement::getAllChildNode()
{	
	return childNode;
}
vector<xmlNode*> * xmlElement::getAllChildNodeVector()
{	
	return &childNode;
}	
xmlNode* xmlElement::getChildNode(int i)
{
	return childNode[i];
}
vector<xmlElement*> xmlElement::getAllChildElement()
{
	return childElement;
}
vector<xmlElement*> * xmlElement::getAllChildElementVector()
{	
	return &childElement;
}
xmlElement* xmlElement::getChildElement(int i)
{
	return childElement[i];
}	
xmlElement * xmlElement::getParent()
{
	return parentElement;
}

//Setter
void xmlElement::setParent(xmlElement * elParent)
{
	parentElement = elParent;
}

//Ajout d'attribut
void xmlElement::addAttribute(attribute* elAtt)
{
	att.push_back(elAtt);
}
//Ajout de noeud enfant
void xmlElement::addXmlNode(xmlNode * elNode)
{
	//Ajout d'un noeud enfant dans le vecteur de noeud enfant
	childNode.push_back(elNode);
	childNodeCount++;
	xmlElement * elElement = dynamic_cast<xmlElement*>(elNode);
	if (elElement != 0) // Si c'est un xmlElement
	{
		//Ajout d'un élément dans le vecteur element
		childElement.push_back(elElement);
		childElementCount++;
		elElement->setParent(this);//On set le parent de cet element
	}
}
//Retrait d'un noeud enfant
void xmlElement::removeXmlNode()
{
	//On essai un cast en xmlElement du noeud à retiré
	xmlElement * elElement = dynamic_cast<xmlElement*>(childNode[childNode.size()-1]);
	//On retire le noeud du vecteur de noeud enfant
	childNode.pop_back();
	childNodeCount--;
	if (elElement != 0) // Si c'est un xmlElement
	{
		//On retire l'élement du vecteur d'élement
		childElement.pop_back();
		childElementCount--;
	}
	delete(elElement);
}
//Recherche d'un element par son nom
xmlElement * xmlElement::getElementByName(string elName)
{
	//On parcourt le vecteur d'element
	for(int i = 0; i < childElementCount; i++)
	{
		if (childElement[i]->name == elName)//Si on trouve l'element
		{
			return childElement[i];
		}
		else//Sinon, on parcour l'enfant pour voir s'il n'est pas dedans
		{
			xmlElement* result = getElementByName(name);
			if (result != NULL)
				return result;
		}
	}
	//Renvoi NULL si non trouvé
	return NULL;
}
//Recherche d'un element par nom complet 'ns:name'
xmlElement * xmlElement::getElementByFullName(string elName)
{
	for(int i = 0; i < childElementCount; i++)
	{
		if (childElement[i]->getFullName() == elName)
		{
			return childElement[i];
		}
		else
		{
			xmlElement* result = childElement[i]->getElementByFullName(elName);
			if (result != NULL)
				return result;
		}
	}
	return NULL;
}

//Copy complète du noeud
xmlElement * xmlElement::copy ()
{
	//Creation du noeud à renvoyer
	xmlElement * newEltResult;
	if (ns == "")//Si pas de namespace
		newEltResult = new xmlElement(name);
	else //Sinon
		newEltResult = new xmlElement(name,ns);
	//On parcour les noeud enfant que l'on va copier
	for (int i = 0 ; i < childNode.size() ; i++)
	{
		//Creation des noeuds enfant temporaire que l'on va copier
		xmlNode * tempChild = childNode[i];
		//On cast en xmlElement
		xmlElement * tempElement =  dynamic_cast<xmlElement*>(tempChild);
		if(tempElement != NULL)//Si l'enfant est un xmlElement
		{
			//On ajout sa copie complète au vecteurs du noeud à renvoyer
			newEltResult->addXmlNode(tempElement->copy());
		}	
		else//Sinon, l'enfant est du text
		{
			//On crée un nouveau noeud text avec le contenu du text à copier
			xmlText * tempText =  new xmlText(((xmlText*)tempChild)->getText());
			//On l'ajoute aux vecteurs du noeud à renvoyer
			newEltResult->addXmlNode(tempText);
		}
	}
	return newEltResult;
}
//Affichage de l'arbre xml dans le terminal
void xmlElement::display()
{
	//Si présence d'un namespace
	if (ns=="")
		cout << "<" << name ;
	else//Sinon
		cout << "<" << ns << ":" << name ;
	//S'il y a des attributs
	if (att.size() > 0)
		//On affiche les attributs
		for (int i = 0 ; i < att.size() ; i++)
			cout << " " << att[i]->id << "='" << att[i]->value << "'";
	//S'il n'y a pas de noeud enfant, on ferme la balise
	if (childNode.size() == 0)
		cout << "/>" << endl;
	else//Sinon
	{	
		cout << ">" << endl;
		//Pour chaque noeud enfant
		for (int i = 0 ; i < childNode.size() ; i++)
		{
			//On affiche le noeud enfant
			childNode[i]->display();
		}
		//On ferme la balise
		if (ns=="")
			cout << "</" << name << ">" << endl;
		else
			cout << "</" << ns << ":" << name << ">" <<endl;
	}
}
//Ecriture de l'arbre dans un string.
//Même méthode que pour le display
string xmlElement::write()
{
	string result = "";
  	if (ns=="")
		result += "<"+name ;
	else
		result += "<" + ns + ":" + name ;
	if (att.size() > 0)
		for (int i = 0 ; i < att.size() ; i++)
			result += " " + att[i]->id + "='" + att[i]->value + "'";
	if (childNode.size() == 0)
		result += "/> \n";
	else
	{	
		result += "> \n" ;
		for (int i = 0 ; i < childNode.size() ; i++)
			result += childNode[i]->write();
		if (ns=="")
			result += "</" + name + "> \n" ;
		else
			result += "</" + ns + ":" + name + ">";
	}
	return result;
}
