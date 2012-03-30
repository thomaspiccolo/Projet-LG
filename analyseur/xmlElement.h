#ifndef XMLELEMENT_H
#define XMLELEMENT_H

#include <vector>
#include <string>
#include "xmlNode.h"

using namespace std;

/*Définition d'une structure attribut*/
typedef struct attribute{
	string id;
	string value;
};

/*Classe xmlElement : Enfant de xmlNode, comportant les balises XML*/
class xmlElement : public xmlNode {
	
	// Privée
	private:
	//Namespace
	string ns;
	//Nom de la balise
	string name;
	//Vecteur stockant les attributs de la balise
	vector<attribute*> att;
	//Compteur de noeud enfant et d'element XML enfant
	int childElementCount;
	int childNodeCount;
	//Vecteur de noeuf enfant et d'element XML enfant
	vector<xmlNode*> childNode;
	vector<xmlElement*> childElement;
	//Pointeur vers le parent du noeud XML
	xmlElement * parentElement;
	

	//Publique
	public:

	//Constructeurs
	xmlElement(string name);
	xmlElement(string name, string ns);
	//Destructeur
	~xmlElement();
	
	//Getteur
	string getName();
	string getNameSpace();
	string getFullName(); 								// Renvoi 'ns:name'
	vector<attribute*> getAllAttributes(); 				//Renvoi le vecteur d'attribut
	attribute * getAttribute(int i); 					//Renvoi l'attribut i du vecteur d'attribut
	int getAttributeCount(); 							//Renvoi le nombre d'attribut
	int getChildElementCount(); 						//Renvoi le nombre d'element enfant
	int getChildNodeCount();							//Renvoi le nombre de noeud enfant
	vector<xmlNode*> getAllChildNode();					//Renvoi le vecteur de noeud enfant
	vector<xmlNode*> * getAllChildNodeVector();			//Renvoi un pointeur vers le vecteur de noeud d'enfant
	xmlNode* getChildNode(int i);						//Renvoi le noeud enfant i
	vector<xmlElement*> getAllChildElement();			//Renvoi le vecteur d'élement enfant
	vector<xmlElement*> * getAllChildElementVector();	//Renvoi un pointeur vers le vecteur d'élement d'enfant
	xmlElement * getChildElement(int i);				//Renvoi l'élement enfant i
	xmlElement * getParent();							//Renvoi le parent

	void setParent(xmlElement * elParent);				//Permet de modifier le noeud parent

	void addAttribute(attribute * elAtt);				//Permet d'ajouter un attribut au noeud
	void addXmlNode(xmlNode * elNode);					//Permet d'ajouter un noeud enfant au noeud, que ce soit un xmlElement ou xmlText
	void removeXmlNode();								//Permet de retire un noeud enfant au noeud, que ce soit un xmlElement ou xmlText

	xmlElement * getElementByName(string name);			//Renvoi un élement que l'on cherche à partir de son nom
	xmlElement * getElementByFullName(string elName);	//Renvoi un élement que l'on cherche à partir de son nom complé (ie ns:name)
	xmlElement * copy ();								//Renvoi un pointeur vers une copy complète de l'élement

	void display();										//Affiche l'arbre à partir du noeud dans le terminal
	string write();										//Renvoi un string comportant l'arbre à partir du noeud
};

#endif
