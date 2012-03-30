/*************************************************************************
                           Name  -  description
                             -------------------
    debut                : 2012-3-20
    copyright            : (C) 2012
*************************************************************************/

//---------- Realisation de la classe <Name> (fichier Name.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include systeme
using namespace std;
#include <iostream>

//------------------------------------------------------ Include personnel
#include "Name.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Methodes publiques


void Name::setName(string nom)
// Algorithme :
//
{
	name = nom;
}


string Name::DisplayCP ( )
// Algorithme :
//
{
	return name + OPT;
}//----- Fin de Main

//------------------------------------------------- Surcharge d'operateurs

//-------------------------------------------- Constructeurs - destructeur

Name::Name(string nom):CP()
// Algorithme :
//
{
	name = nom;
} //----- Fin de DtdElement


Name::~Name( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Name>" << endl;
#endif
} //----- Fin de ~Name


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Methodes protegees
