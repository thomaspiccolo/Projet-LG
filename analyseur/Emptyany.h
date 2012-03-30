/*************************************************************************
                           Emptyany  -  description
                             -------------------
    debut                : 2012-3-30
    copyright            : (C) 2012 par DARK
*************************************************************************/

//----- Interface de la classe <Emptyany> (fichier Emptyany.h) -----
#if ! defined ( EMPTYANY_H_ )
#define EMPTYANY_H_

//--------------------------------------------------- Interfaces utilisees
#include "DtdElement.h"
//------------------------------------------------------------- Constantes 

//------------------------------------------------------------------ Types 

//------------------------------------------------------------------------ 
// Role de la classe <Emptyany>
//
//
//------------------------------------------------------------------------ 

class Emptyany : public DtdElement
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Methodes publiques
    // type Methode ( liste des parametres );
    // Mode d'emploi :
    //
    // Contrat :
    //
	void SetEmpty(bool emp);
	void Display();


//------------------------------------------------- Surcharge d'operateurs

//-------------------------------------------- Constructeurs - destructeur

    Emptyany ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Emptyany ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE 

protected:
//----------------------------------------------------- Methodes protegees

//----------------------------------------------------- Attributs proteges
bool empty;
};

//--------------------------- Autres definitions dependantes de <Emptyany>

#endif // EMPTYANY_H_
