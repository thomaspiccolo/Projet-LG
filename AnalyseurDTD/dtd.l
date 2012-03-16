%option 8bit 

%{
#include <ctype.h>
#include <string.h>
#include "yy.tab.h"

static char* skipSpace(char *s) {
  char *buf;
  int i,lastnonspace;
  for (buf=s;isspace(*buf);buf++) ;
  for (i=0,lastnonspace=0;buf[i];i++) {
     if (!isspace(buf[i]))
        lastnonspace = i;
  }
  buf[lastnonspace+1] = '\0';
  return strdup(buf);
}
  
/* affecte la valeur de la chaine de caractère et renvoie le token */
#define stringreturn(tokenval) yylval.s=skipSpace(yytext);return(tokenval)

%}
%option noyywrap

nl		(\r\n|\r|\n)
ws		[ \t\r\n]+
open		{nl}?"<"
close		">"{nl}?
openpar "("
closepar ")"
comma ","
pipe "|"
esc		"&#"[0-9]+";"|"&#x"[0-9a-fA-F]+";"
namestart	[A-Za-z\200-\377_]
namechar	[A-Za-z\200-\377_0-9.-]
tokentype "ID"|"IDREF"|"IDREFS"|"ENTITY"|"ENTITIES"|"NMTOKEN"|"NMTOKENS"
name		{namestart}{namechar}*
comment		{open}"!--"([^-]|"-"[^-])*"--"{close}
string		\"([^"&]|{esc})*\"|\'([^'&]|{esc})*\'
element {open}"!ELEMENT"{ws}
attlist {open}"!ATTLIST"{ws}
declaration "#"("REQUIRED"|"IMPLIED"){ws}?
fixed "#FIXED"{ws}
pcdata "#PCDATA"{ws}?
cdata "CDATA"{ws}?
qmark "?"
ast "*"
plus "+"
empty "EMPTY"
any "ANY"

%s INSIDE

/* 
   INITIAL : en dehors d'un bloc ELEMENT ou ATTLIST
   INSIDE : dans un bloc ELEMENT ou ATTLIST
*/

%%

<INITIAL>{ws}		            { printf(yytext);/* skip */}
<INITIAL>{element}            { printf(yytext);BEGIN(INSIDE); return ELEMENT; }
<INITIAL>{attlist}            { printf(yytext);BEGIN(INSIDE); return ATTLIST; }
<INSIDE>{close}               { printf(yytext);BEGIN(INITIAL); return CLOSE; }
<INSIDE>{openpar}             { printf(yytext);return OPENPAR; }
<INSIDE>{closepar}{ws}?       { printf(yytext);return CLOSEPAR; }
<INSIDE>{comma}{ws}?          { printf(yytext);return COMMA; }
<INSIDE>{pipe}{ws}?           { printf(yytext);return PIPE; }
<INSIDE>{declaration}         { printf(yytext);stringreturn(DECLARATION); }
<INSIDE>{fixed}               { printf(yytext);return FIXED; }
<INSIDE>{ast}                 { printf(yytext);return AST ; }
<INSIDE>{qmark}               { printf(yytext);return QMARK ; }
<INSIDE>{plus}                { printf(yytext);return PLUS ; }
<INSIDE>{empty}               { printf(yytext);return EMPTY; }
<INSIDE>{any}                 { printf(yytext);return ANY; }
<INSIDE>{pcdata}              { printf(yytext);return PCDATA; }
<INSIDE>{cdata}               { printf(yytext);return CDATA; }
<INSIDE>{string}              { printf(yytext);stringreturn(STRING); }
<INSIDE>{tokentype}{ws}?      { printf(yytext);stringreturn(TOKENTYPE); }
<INSIDE>{name}{ws}?           { printf(yytext);stringreturn(IDENT); }
{comment}		               { /* skip comments stringreturn(COMMENT); */ }

{nl}                    {printf("%s",yytext);/* skip, must be an extra one at EOF */;}
.			{ fprintf(stderr, "!ERROR(%c)\n", *yytext);}
