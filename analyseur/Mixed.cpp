/*************************************************************************
                           Mixed  -  description
                             -------------------
    debut                : 2012-3-20
    copyright            : (C) 2012
*************************************************************************/

//---------- Realisation de la classe <Mixed> (fichier Mixed.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include systeme
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Mixed.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Methodes publiques
void Mixed::AddName (string nom)
// Algorithme :
//
{
	list_noms.push_back(nom);
}

void Mixed::AddNameList(list<string> listName)
// Algorithme :
//
{
	list_noms = listName;
}


void Mixed::Display ( )
// Algorithme :
//
{
	string mixed;
	mixed="<!ELEMENT "+ident+" (#PCDATA";
	list <string>::iterator iter;
	for(iter=list_noms.begin();iter!=list_noms.end();iter++)
	{
		mixed=mixed+"|"+(*iter);
	}
	mixed = mixed+")";
	if(list_noms.size()>0)
	{
		mixed=mixed+"*";
	}
	mixed = mixed+">";
	cout<<mixed<<endl;
}//----- Fin de Main

//------------------------------------------------- Surcharge d'operateurs

//-------------------------------------------- Constructeurs - destructeur

Mixed::Mixed(string ident):DtdElement(ident)
// Algorithme :
//
{
} //----- Fin de DtdElement


Mixed::~Mixed ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <DtdElement>" << endl;
#endif
} //----- Fin de ~DtdElement


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Methodes protegees
