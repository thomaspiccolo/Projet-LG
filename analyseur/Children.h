/*************************************************************************
                           Children -  description
                             -------------------
    debut                : 2012-03-20
    copyright            : (C) 2012
*************************************************************************/

//----- Interface de la classe <Children> (fichier Children.h) -----
#ifndef Children_H_
#define Children_H_

//--------------------------------------------------- Interfaces utilisees
#include <string>
#include <list>
#include "CP.h"

//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types

//------------------------------------------------------------------------
// Role de la classe <Coordinateur>
//
//
//------------------------------------------------------------------------

class Children : public CP
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Methodes publiques

	  void AddCP(CP* unCP);
      // Mode d'emploi :
      //
      //
      // Contrat :
      //

	  void SetListCP(list <CP*> unListCP);
	  // Mode d'emploi :
	  //
	  //
	  // Contrat :
	  //

	  void SetChoiceSeq(bool choice);
      // Mode d'emploi :
      //
      //
      // Contrat :
      //

	  string DisplayCP ( );
	  // Mode d'emploi :
	  //
	  // Cette méthode sert à afficher une structure Mixed


//------------------------------------------------- Surcharge d'operateurs

//-------------------------------------------- Constructeurs - destructeur
	  Children(string id="");
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Children ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Methodes protegees

//----------------------------------------------------- Attributs proteges
    list<CP*> listCP;
    bool ChoiceSeq;
};

//--------------------------- Autres definitions dependantes de <Coordinateur>

#endif /* Children_H */
