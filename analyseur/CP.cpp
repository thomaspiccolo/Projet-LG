/*************************************************************************
                           CP  -  description
                             -------------------
    debut                : 2012-3-20
    copyright            : (C) 2012
*************************************************************************/

//---------- Realisation de la classe <CP> (fichier CP.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include systeme
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "CP.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Methodes publiques

void CP::SetOPT(string unOPT)
{
	OPT = unOPT;
}


void CP::Display ( )
// Algorithme :
//
{
	cout<<"<!ELEMENT " + ident + " ";
	cout<<this->DisplayCP()+">\n";
}//----- Fin de Main

string CP::DisplayCP()
{

}

//------------------------------------------------- Surcharge d'operateurs

//-------------------------------------------- Constructeurs - destructeur

CP::CP(string id):DtdElement(id)
// Algorithme :
//
{
	OPT = "";
} //----- Fin de DtdElement


CP::~CP( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <CP>" << endl;
#endif
} //----- Fin de ~DtdElement


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Methodes protegees
