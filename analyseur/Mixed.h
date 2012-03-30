/*************************************************************************
                           Mixed  -  description
                             -------------------
    debut                : 2012-03-20
    copyright            : (C) 2012
*************************************************************************/

//----- Interface de la classe <Mixed> (fichier Mixed.h) -----
#ifndef MIXED_H_
#define MIXED_H_

//--------------------------------------------------- Interfaces utilisees
#include <string>
#include <list>
#include "DtdElement.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Role de la classe <Coordinateur>
//
//
//------------------------------------------------------------------------

class Mixed : public DtdElement
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Methodes publiques

	  void AddName (string nom);
      // Mode d'emploi :
      //
      //
      // Contrat :
      //

	  void AddNameList (list <string> listName);
      // Mode d'emploi :
      //
      //
      // Contrat :
      //

	  void Display ( );
	  // Mode d'emploi :
	  //
	  // Cette méthode sert à afficher une structure Mixed


//------------------------------------------------- Surcharge d'operateurs

//-------------------------------------------- Constructeurs - destructeur
    Mixed (string ident="");
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Mixed ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Methodes protegees

//----------------------------------------------------- Attributs proteges
    list <string> list_noms;
};

//--------------------------- Autres definitions dependantes de <Coordinateur>

#endif /* Mixed_H */
