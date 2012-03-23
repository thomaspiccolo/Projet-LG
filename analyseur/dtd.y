%{
using namespace std;
/*#include "Dtd.h" 
*/
void dtderror(char *msg);
int dtdwrap(void);
int dtdlex(void);

/*
Dtd * myDtd;
DtdElement * currentElem;
string identAttlist;
*/
%}

%union { 
   char *s; 
}

%token ELEMENT ATTLIST CLOSE OPENPAR CLOSEPAR COMMA PIPE FIXED EMPTY ANY PCDATA AST QMARK PLUS CDATA
%token <s> IDENT TOKENTYPE DECLARATION STRING

%%

main: 
dtd_list_opt 
/*{
	myDtd = new Dtd();
}*/
;

dtd_list_opt
: dtd_list_opt ATTLIST IDENT att_definition_opt CLOSE
/*{
	identAttlist = $2;
}*/
| dtd_list_opt ELEMENT IDENT element_content CLOSE
| /* empty */                     
;

element_content
: children 
| cp 
| choice
| seq
| mixed 
| /* empty */                     
;

mixed 
: OPENPAR mixed_content CLOSEPAR
;

mixed_content
: PCDATA mixed_content_opt
; 

mixed_content_opt
: IDENT list_noms
| /* empty */
;

list_noms
: IDENT PIPE mixed_content_opt
;

children
: choice_card
| seq_card
;

choice_card 
: choice card_opt
;

seq_card 
: seq card_opt
;

card_opt
: QMARK 
| PLUS
| AST
| /* empty */
;

choice 
: OPENPAR choice_list_plus CLOSEPAR
;

choice_list 
: choice_list PIPE cp
|cp
;

choice_list_plus:
cp PIPE choice_list
;

seq : 
OPENPAR seq_list CLOSEPAR
;

seq_list : seq_list COMMA cp
|cp
;

cp 
: IDENT card_opt
| children
;


att_definition_opt
: att_definition_opt attribute
| /* empty */
;

attribute
: IDENT att_type default_declaration
;

att_type
: CDATA    
| TOKENTYPE
| enumerate
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

default_declaration
: DECLARATION 
| STRING     
| FIXED STRING 
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


