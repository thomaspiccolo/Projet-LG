%{
#include <string.h>
#include "commun.h"
#include "CP.h"
#include "Dtd.h" 
#include "Name.h"
#include "Mixed.h"
#include "Children.h"
#include "Emptyany.h"
#include "DtdElement.h"

void dtderror(char *msg);
int dtdwrap(void);
int dtdlex(void);

Dtd * unDtd = new Dtd();
string ident;
string opt;
list <string> listNoms;
list <CP *> listCp;
list <CP *> subListCp;
DtdElement * currentElem = NULL;
Mixed * mixedElem = NULL;
Children * childElem = NULL;
Children * subChildElem = NULL;
Name * nameElem = NULL;
Emptyany * emptyAnyElem = NULL;
int typeElem = 0;
int subChildren = 0;
int childrenOPT = 0;
int nameOPT = 0;
int empty = 0;
%}

%union { 
   char *s;
}
%token ELEMENT ATTLIST CLOSE OPENPAR CLOSEPAR COMMA PIPE FIXED EMPTY ANY PCDATA AST QMARK PLUS CDATA
%token <s> IDENT TOKENTYPE DECLARATION STRING
%%

main: 
dtd_list_opt 
;

dtd_list_opt
: dtd_list_opt ATTLIST IDENT att_definition_opt CLOSE
{
	// enregistrement du IDENT de ATTLIST
	ident = $3;
	unDtd->AddAttList(ident, listNoms);
	listNoms.clear();
}
| dtd_list_opt ELEMENT IDENT element_content CLOSE
{
	// enregistrement du IDENT de ELEMENT
	ident = $3;
	switch(typeElem)
	{
		case 1:
		case 2:
		case 3:
		case 4:
			childElem->SetIdent(ident);
			currentElem = dynamic_cast<Children *>(childElem);
		break;
		
		case 5:
			mixedElem = new Mixed();
			mixedElem->SetIdent(ident);
			mixedElem->AddNameList(listNoms); 
			currentElem = dynamic_cast<Mixed *> (mixedElem);
		break;
		
		case 6:
			emptyAnyElem = new Emptyany();
			emptyAnyElem -> SetIdent(ident);
			emptyAnyElem -> SetEmpty(empty);
			currentElem = dynamic_cast<Emptyany *> (emptyAnyElem);
		break;
		
		default:
			currentElem = new DtdElement();
			currentElem->SetIdent(ident);
  }
	unDtd->AddElement(currentElem);
	currentElem = NULL;
	nameElem = NULL;
	childElem = NULL;
	mixedElem = NULL;
	emptyAnyElem = NULL;
	listNoms.clear();
	typeElem = 0;
	subChildren = 0;
	childrenOPT = 0;
	nameOPT = 0;
	empty = 0;
}
| /* empty */                     
;

att_definition_opt
: att_definition_opt attribute
| /* empty */ 
;

attribute
: IDENT att_type default_declaration
{
	// enregistrement d'un nom d'attribut dans la liste
	listNoms.push_back($1); 
}
;

default_declaration
: DECLARATION 
| STRING     
| FIXED STRING 
;


att_type
: CDATA
| TOKENTYPE
| enumerate
;

element_content
: 
children 
{	typeElem = 1; }
|cp
{ typeElem = 2;	} 
|choice
{ typeElem = 3; }
|seq
{ typeElem = 4; }
|mixed 
{ typeElem = 5; }
|emptyany
{ typeElem = 6; }
| /* empty */                      
;

emptyany
: EMPTY
{ empty = 1; }
| ANY
;


mixed 
: OPENPAR mixed_content CLOSEPAR AST
| OPENPAR PCDATA CLOSEPAR
;

mixed_content
: PCDATA mixed_content_opt
; 

mixed_content_opt
: PIPE list_noms
| /* empty */
;

list_noms
: IDENT mixed_content_opt
{ 
	listNoms.push_front($1);
}
;

children
: choice_card
| seq_card
;

choice_card 
: choice card_opt
{
	if ((subChildren == 1) || (childrenOPT == 1)){
		subChildren = 0;
		subChildElem = NULL;
		childrenOPT = 0;
	}
}
;

seq_card 
: seq card_opt
{
	if ((subChildren == 1) || (childrenOPT == 1)){
		subChildren = 0;
		subChildElem = NULL;
		childrenOPT = 0;
	}
}
;

card_opt
: QMARK 
{ 
	if (nameElem == NULL){	
		nameElem = new Name();
	}
	if (subChildren == 1){
		subChildElem->SetOPT("?");
	} 
	else if (childrenOPT == 1){
		childElem->SetOPT("?");
	}
	else {
		nameElem->SetOPT("?");
	}
}
| PLUS
{
	if (nameElem == NULL){
		nameElem = new Name();
		nameOPT = 1;
	}
	if (nameOPT == 1){
		nameElem->SetOPT("+");
		nameOPT = 0;
	}
	if (subChildren == 1){
		subChildElem->SetOPT("+");
	}
	else if ((childrenOPT == 1)&&(nameOPT == 0)){
		childElem->SetOPT("+");
	}
}
| AST
{
	if (nameElem == NULL){
		nameElem = new Name();
	}
	if (subChildren == 1){
		subChildElem->SetOPT("*");
	}
	else if (childrenOPT == 1){
		childElem->SetOPT("*");
	}
	else {
		nameElem->SetOPT("*");
	}
}
| /* empty */
{
	if (nameElem == NULL){
		nameElem = new Name();
	}
}
;

choice 
: OPENPAR choice_list_plus CLOSEPAR 
{
	if (subChildren == 0){
		childElem->SetChoiceSeq(true);
		childElem->SetListCP(listCp);
		listCp.clear();
		childrenOPT = 1;
	} else {
		subChildElem->SetChoiceSeq(true);
		subChildElem->SetListCP(subListCp);
		listCp.push_back(subChildElem);
		subListCp.clear();
	} 
}
;

choice_list 
: choice_list PIPE cp
| cp
;

choice_list_plus:
cp PIPE choice_list
;

seq : 
OPENPAR seq_list CLOSEPAR
{
	if (subChildren == 0){
		childElem->SetChoiceSeq(false);
		childElem->SetListCP(listCp);
		listCp.clear();
		childrenOPT = 1;
	} else {
		subChildElem->SetChoiceSeq(false);
		subChildElem->SetListCP(subListCp);
		listCp.push_back(subChildElem);
		subListCp.clear();
	}
}
;

seq_list : seq_list COMMA cp
|cp
;

cp 
: IDENT card_opt
{
	if (childElem == NULL){
		childElem = new Children();
	}
	if (nameElem != NULL)
	{
		nameElem->setName($1);
	}
	if ( subChildren == 0 ) {
		listCp.push_back(nameElem);
	} else {
		subListCp.push_back(nameElem);
	}	
	nameElem = NULL;}
|
{
	subChildElem = new Children();
	subChildren = 1;
}
children
{	nameElem = NULL;}
;

enumerate
: OPENPAR enum_list_plus CLOSEPAR
;

enum_list_plus
: enum_list PIPE item_enum
;

enum_list
: item_enum               
| enum_list PIPE item_enum
;

item_enum
: IDENT
;

%%

int dtdwrap(void)
{
  return 1;
}

void dtderror(char *msg)
{
  fprintf(stderr, "%s\n", msg);
}