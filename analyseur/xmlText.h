#ifndef XMLTEXT_H
#define XMLTEXT_H

#include "xmlNode.h"
#include <string>
#include <iostream>

/*Classe xmlText : hérité de xmlNode*/
class xmlText : public xmlNode{
	//Privée
	private:
	//Attribut text qui comporte le contenu de la balise
	std::string text;
		
	public:
	//Constructeur
	xmlText(std::string content);
	//Destructeur
	~xmlText();
	//Getter
	std::string getText();
	//Affichage dans le terminale
	void display(); 
	//Renvoi un string avec le contenu
	std::string write();

};

#endif
