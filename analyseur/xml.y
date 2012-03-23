%{

using namespace std;
#include "commun.h"
#include "xmlElement.h"
#include "xmlText.h"
#include <string>

int xmlwrap(void);
void xmlerror(char *msg);
int xmllex(void);

xmlElement * root;
xmlElement * current;

%}


%union {
   char * s;
   ElementName * en;  /* le nom d'un element avec son namespace */
}

%token EQ SLASH CLOSE CLOSESPECIAL DOCTYPE
%token <s> ENCODING STRING DATA COMMENT IDENT NSIDENT
%token <en> NSSTART START STARTSPECIAL END NSEND

%%

document
 : declarations_opt xml_element misc_seq_opt {current = NULL}
 ;
misc_seq_opt
 : misc_seq_opt comment
 | /*empty*/
 ;
comment
 : COMMENT
 ;

declarations_opt
 : declaration
 | /*empty*/
 ;
 
declaration
 : DOCTYPE IDENT IDENT STRING CLOSE 
 ;

xml_element
 : start attribute_opt empty_or_content 
 ;
start
 : START
 		{
 			if (current==NULL)
 		  	{
 				root = new xmlElement($1->second);
 				current = root;
 			}
 			else
 			{
 				xmlElement * newElement = new xmlElement($1->second);
				current->addXmlNode(newElement);
 				current = newElement;
 			}
		}
 				
 | NSSTART
 		{
 			if (current==NULL)
 		  	{
 				root = new xmlElement($1->second,$1->first);
 				current = root;
 			}
 			else
 			{
 				xmlElement * newElement = new xmlElement($1->second,$1->first);
				current->addXmlNode(newElement);
 				current = newElement;
 			}
 		}
 ;
attribute_opt
 : attribute_opt attribute
 | /*empty*/
 ;
attribute
 : IDENT EQ STRING 
 		{
 			attribute * newAtt = new attribute;
 			newAtt->id = $1;
 			newAtt->value = $3;
 			current->addAttribute(newAtt);
 		}
 | NSIDENT EQ STRING
		{
			attribute * newAtt = new attribute;
			newAtt->id = $1;
			newAtt->value = $3;
			current->addAttribute(newAtt);
		}
 ;
empty_or_content
 : SLASH CLOSE
 		{
 			current=current->getParent();
 		}	
 | close_content_and_end CLOSE
 		{
 			current=current->getParent();
 		} 
 ;
close_content_and_end
 : CLOSE content_opt END
 | CLOSE content_opt NSEND 
 ;
content_opt 
 : content_opt DATA
 		{
 			xmlText * newContent = new xmlText($2);
 			current->addXmlNode(newContent);
 		}		
 | content_opt comment        
 | content_opt xml_element   
 | /*empty*/         
 ;
%%

/*int main(int argc, char **argv)
{
  int err;

  yydebug = 1; // pour enlever l'affichage de l'éxécution du parser, commenter cette ligne

  err = yyparse();
  if (err != 0) printf("Parse ended with %d error(s)\n", err);
  	else  printf("Parse ended with success\n", err);
  root->display();
  return 0;
}*/

int xmlwrap(void)
{
  return 1;
}

void xmlerror(char *msg)
{
  fprintf(stderr, "%s\n", msg);
}

