/*************************************************************************
                           DtdElement  -  description
                             -------------------
    debut                : 2012-3-20
    copyright            : (C) 2012
*************************************************************************/

//-- Realisation de la classe <DtdElement> (fichier DtdElement.cpp) ------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include systeme
using namespace std;
#include <iostream>
//------------------------------------------------------ Include personnel
#include "DtdElement.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Methodes publiques


void DtdElement::Display()
{
}

void DtdElement::SetIdent(string id)
{
	ident = id;
}

//------------------------------------------------- Surcharge d'operateurs

//-------------------------------------------- Constructeurs - destructeur

DtdElement::DtdElement(string elem_name)
// Algorithme :
//
{
	ident = elem_name;
} //----- Fin de DtdElement

string DtdElement::GetIdent()
{
	return ident;
}

DtdElement::~DtdElement ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <DtdElement>" << endl;
#endif
} //----- Fin de ~DtdElement


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Methodes protegees
