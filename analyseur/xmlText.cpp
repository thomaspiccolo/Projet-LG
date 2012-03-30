#include "xmlText.h"
#include "xmlNode.h"
#include <string>
#include <iostream>

using namespace std;

//Constructeur
xmlText::xmlText(std::string content)
{
	text = content;
}
//Destructeur
xmlText::~xmlText()
{
}	
//Getter de text qui renvoi le text
string xmlText::getText()
{
	return text;
}
//Affiche le text dans le terminal
void xmlText::display()
{
	cout << text << endl;	
}
//Renvoi un string avec le contenu
string xmlText::write()
{
	return (text+"\n");	
}
