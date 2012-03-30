/*************************************************************************
                           Emptyany  -  description
                             -------------------
    debut                : 2012-3-30
    copyright            : (C) 2012 par DARK
*************************************************************************/

//---------- Realisation de la classe <Emptyany> (fichier Emptyany.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include systeme
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Emptyany.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Methodes publiques
// type Emptyany::Methode ( liste des parametres )
// Algorithme :
//
//{
//} //----- Fin de Methode

void Emptyany::SetEmpty(bool emp)
// Algorithme :
//
{
	empty = emp;
}

void Emptyany::Display()
// Algorithme :
//
{
	cout << "<!ELEMENT " << ident;
	if (empty == true){
		cout << " EMPTY>" << endl;
	} else {
		cout << " ANY>" << endl;
	}
}


//------------------------------------------------- Surcharge d'operateurs

//-------------------------------------------- Constructeurs - destructeur
Emptyany::Emptyany ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Emptyany>" << endl;
#endif
} //----- Fin de Emptyany


Emptyany::~Emptyany ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Emptyany>" << endl;
#endif
} //----- Fin de ~Emptyany


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Methodes protegees

