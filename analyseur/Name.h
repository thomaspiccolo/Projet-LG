/*************************************************************************
                           Name -  description
                             -------------------
    debut                : 2012-03-20
    copyright            : (C) 2012
*************************************************************************/

//----- Interface de la classe <Name> (fichier Name.h) -----
#ifndef Name_H_
#define Name_H_

//--------------------------------------------------- Interfaces utilisees
#include <string>
#include <list>
#include "CP.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Role de la classe <Name>
//
//
//------------------------------------------------------------------------

class Name : public CP
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Methodes publiques

	  void setName(string nom);
      // Mode d'emploi :
      //
      //
      // Contrat :
      //

	  string DisplayCP ( );
	  // Mode d'emploi :
	  //
	  // Cette méthode sert à afficher Name


//------------------------------------------------- Surcharge d'operateurs

//-------------------------------------------- Constructeurs - destructeur
	 Name(string nom="");
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Name ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Methodes protegees

//----------------------------------------------------- Attributs proteges
    string name;
};

//--------------------------- Autres definitions dependantes de <Name>

#endif /* Name_H */
