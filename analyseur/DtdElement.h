/*************************************************************************
                           DtdElement  -  description
                             -------------------
    debut                : 2012-03-20
    copyright            : (C) 2012 par Yachen HUANG & Xiao-Jing LIU
*************************************************************************/

//----- Interface de la classe <DtdElement> (fichier DtdElement.h) -----
#ifndef DTDELEMENT_H_
#define DTDELEMENT_H_

using namespace std;
//--------------------------------------------------- Interfaces utilisees
#include <cstdlib>
#include <string>
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Role de la classe <DtdElement>
//
//
//------------------------------------------------------------------------

class DtdElement
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Methodes publiques


	virtual void Display();
	// Mode d'emploi :
	// Cette fonction permet d'afficher un element
	// Contrat :

	void SetIdent(string id);
	// Mode d'emploi :
	//Cette fonction permet d'afficher un element
	// Contrat :

	string GetIdent();
	// Mode d'emploi :
	//Cette fonction permet d'afficher un element
	// Contrat :

//------------------------------------------------- Surcharge d'operateurs

//-------------------------------------------- Constructeurs - destructeur
	DtdElement(string elem_name = "");
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~DtdElement ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Methodes protegees

//----------------------------------------------------- Attributs proteges
	string ident;
};

//--------------------------- Autres definitions dependantes de <DtdElement>

#endif /* DTDELEMENT_H_ */
