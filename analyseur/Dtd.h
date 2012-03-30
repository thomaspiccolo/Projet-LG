/*************************************************************************
                           Dtd  -  description
                             -------------------
    debut                : 2012-03-20
    copyright            : (C) 2012
*************************************************************************/

//----- Interface de la classe <Dtd> (fichier Dtd.h) -----
#ifndef DTD_H_
#define DTD_H_

//--------------------------------------------------- Interfaces utilisees
#include <string>
#include <map>
#include <list>
#include "DtdElement.h"
//------------------------------------------------------------- Constantes

//------------------------------------------------------------------ Types
typedef multimap <string, string> attList;
typedef list <string> attNomList;

//------------------------------------------------------------------------
// Role de la classe <Coordinateur>
//
//
//------------------------------------------------------------------------

class Dtd
{
//----------------------------------------------------------------- PUBLIC

public:
//----------------------------------------------------- Methodes publiques

	  void AddElement ( DtdElement* myelem );
	   // Mode d'emploi :
	   //
	   //
	   // Contrat :
	   //

	  void AddAttribut ( string ident,  string attNom ) ;
      // Mode d'emploi :
      //
      //
      // Contrat :
      //

	  void AddAttList ( string ident,  list <string> attNoms ) ;
	  // Mode d'emploi :
	  //
	  //
	  // Contrat :
	  //

	  void Display ( ) const ;
	  // Mode d'emploi :
	      //
	      //
	      // Contrat :
	      //


//------------------------------------------------- Surcharge d'operateurs

//-------------------------------------------- Constructeurs - destructeur
    Dtd ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

    virtual ~Dtd ( );
    // Mode d'emploi :
    //
    // Contrat :
    //

//------------------------------------------------------------------ PRIVE

protected:
//----------------------------------------------------- Methodes protegees

//----------------------------------------------------- Attributs proteges
attList mapElemsAttributs;
list <DtdElement*> listElements;
};

//--------------------------- Autres definitions dependantes de <Coordinateur>

#endif /* DTD_H_ */

