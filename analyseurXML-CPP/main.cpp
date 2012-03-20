#include <stdio.h>
#include <iostream.h>
#include <string.h>

#include "xmlNode.h"
#include "xmlText.h"
#include "xmlElement.h"

using namespace std;

int main22 (int argc, char * argv[])
{
	//xmlElement * lastElementAdded = NULL;
	xmlElement * root = new xmlElement("Rapport");
	//lastElementAdded = root;
	xmlElement * titre = new xmlElement("Titre");
	attribute * elAtt = new attribute;
	elAtt->id="année";
	elAtt->value="2012";
	titre->addAttribute(elAtt);
	xmlText * contentTitre = new xmlText("Réaliser un compilateur");
	titre->addXmlNode(contentTitre);
	root->addXmlNode(titre);
	//lastElementAdded = titre;
	xmlElement * auteur = new xmlElement("Auteur");
	attribute * elAtt2 = new attribute;
	elAtt2->id="nationalité";
	elAtt2->value="Belge";
	attribute * elAtt3 = new attribute;
	elAtt3->id="religion";
	elAtt3->value="juif";
	auteur->addAttribute(elAtt2);
	auteur->addAttribute(elAtt3);
	xmlElement * nom = new xmlElement("Nom");
	xmlText * contenNom = new xmlText("Nino");
	nom->addXmlNode(contenNom);
	auteur->addXmlNode(nom);
	xmlElement * prenom = new xmlElement("Prénom");
	xmlText * contentPrenom = new xmlText("Silverio");
	prenom->addXmlNode(contentPrenom);
	auteur->addXmlNode(prenom);
	root->addXmlNode(auteur);
	
	cout << ((xmlText*)((xmlElement*)root->getChildNode(0))->getChildNode(0))->getText() <<endl;
	return 0;
}
