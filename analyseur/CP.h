/*************************************************************************
                           CP -  description
                             -------------------
    debut                : 2012-03-20
    copyright            : (C) 2012
*************************************************************************/

//----- Interface de la classe <CP> (fichier CP.h) -----
#ifndef CP_H_
#define CP_H_

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

class CP : public DtdElement
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Methodes publiques

	  void SetOPT(string unOPT);
      // Mode d'emploi :
      //
      //
      // Contrat :
      //

	   void Display ( );
	   // Mode d'emploi :
	  	  //
	  	  // Cette méthode sert à afficher une structure Mixed


	   virtual string DisplayCP();
	   // Mode d'emploi :
	  	  //
	  	  // Cette méthode sert à afficher une structure Mixed

//------------------------------------------------- Surcharge d'operateurs

//-------------------------------------------- Constructeurs - destructeur
	CP(string id="");
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~CP ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Methodes protegees

//----------------------------------------------------- Attributs proteges
    string OPT;
};

//--------------------------- Autres definitions dependantes de <Coordinateur>

#endif /* CP_H */
