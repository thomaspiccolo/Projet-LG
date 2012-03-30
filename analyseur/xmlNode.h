#ifndef XMLNODE_H
#define XMLNODE_H

#include <string>
#include <iostream>


/* XML Node : Classe mère de notre structure XML */
class xmlNode
{

	public:
	/*Constructeur*/
	xmlNode();
	/*Destructeur*/
	virtual ~ xmlNode();
	
	/*Affichage de l'arbre dans le terminal */
	virtual void display();	
	/*Ecriture de l'arbdre dans un string */
	virtual std::string write();	
};

#endif
