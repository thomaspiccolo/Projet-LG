/*************************************************************************
                           Children  -  description
                             -------------------
    debut                : 2012-3-20
    copyright            : (C) 2012
*************************************************************************/

//---------- Realisation de la classe <Children> (fichier Children.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include systeme
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Children.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Methodes publiques

void Children::AddCP(CP* unCP)
{
	listCP.push_back(unCP);
}

void Children::SetListCP(list <CP*> unListCP)
{
	listCP = unListCP;
}

void Children::SetChoiceSeq(bool choice)
{
	ChoiceSeq=choice;
}
string Children::DisplayCP ( )
// Algorithme :
//
{
	string str_children = "";
	string seperator=ChoiceSeq?"|":",";
	if (listCP.size() > 0){
		str_children += "(";
		list <CP*>::iterator iter = listCP.begin();
		str_children += (*iter)->DisplayCP();
		iter++;
		for(iter ; iter!=listCP.end(); iter++)
		{
			str_children += seperator+(*iter)->DisplayCP();;
		}
		str_children += ")"+ OPT;
	}
	return str_children;
}//----- Fin de DisplayCP

//------------------------------------------------- Surcharge d'operateurs

//-------------------------------------------- Constructeurs - destructeur

Children::Children(string id):CP(id)
// Algorithme :
//
{
} //----- Fin de DtdElement


Children::~Children( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Children>" << endl;
#endif
} //----- Fin de ~Children


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Methodes protegees
