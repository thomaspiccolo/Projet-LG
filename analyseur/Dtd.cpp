/*************************************************************************
                           Dtd  -  description
                             -------------------
    debut                : 2012-3-20
    copyright            : (C) 2012
*************************************************************************/

//---------- Realisation de la classe <Flot> (fichier Flot.cpp) -------

//---------------------------------------------------------------- INCLUDE

//-------------------------------------------------------- Include systeme
using namespace std;
#include <iostream>
//------------------------------------------------------ Include personnel
#include "Dtd.h"

//------------------------------------------------------------- Constantes

//----------------------------------------------------------------- PUBLIC

//----------------------------------------------------- Methodes publiques

void Dtd::AddElement(DtdElement* myelem)
// Algorithme :
//
{
	listElements.push_back(myelem);
}//----- Fin de addElement

void Dtd::AddAttribut(string ident, string attNom)
// Algorithme :
//
{
	mapElemsAttributs.insert(pair<string,string>(ident,attNom));
} //----- Fin de addAttribut

void Dtd::AddAttList(string ident, list <string> attNoms)
// Algorithme :
//
{
	list<string>::iterator itAttNom;
	for ( itAttNom = attNoms.begin() ; itAttNom != attNoms.end(); itAttNom++ ){
		AddAttribut(ident, (*itAttNom));
	}
} //----- Fin de addAttribut

void Dtd::Display() const
// Algorithme :
// affichage de liste des elements et des attributs
{
	//affichage des DtdElement
	list<DtdElement*>::const_iterator iter_elem;
	for (iter_elem = listElements.begin(); iter_elem != listElements.end(); iter_elem++)
	{
		(*iter_elem)->Display();
	}

	//affichage des attributs
	if (mapElemsAttributs.size() != 0){
		attList myAttList = mapElemsAttributs;
		attList::const_iterator iter_attList;
		pair<attList::iterator, attList::iterator> ret;
		string keyAL;

		while (myAttList.size() !=0){
			iter_attList = myAttList.begin();
			keyAL = (*iter_attList).first;
			cout << "<!ATTLIST " << keyAL << endl;
			ret = myAttList.equal_range(keyAL);
			for (iter_attList = ret.first; iter_attList != ret.second; iter_attList++){
				cout << "        " << (*iter_attList).second << " CDATA #IMPLIED" << endl;
			}
			cout << ">" << endl;
			myAttList.erase(keyAL);
		}
	}
}

//------------------------------------------------- Surcharge d'operateurs

//-------------------------------------------- Constructeurs - destructeur
Dtd::Dtd ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au constructeur de <Dtd>" << endl;
#endif
} //----- Fin de Dtd


Dtd::~Dtd ( )
// Algorithme :
//
{
#ifdef MAP
    cout << "Appel au destructeur de <Dtd>" << endl;
#endif
} //----- Fin de ~Dtd


//------------------------------------------------------------------ PRIVE

//----------------------------------------------------- Methodes protegees
