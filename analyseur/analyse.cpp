using namespace std;
#include "commun.h"
#include "xmlNode.h"
#include "xmlElement.h"
#include "xmlText.h"
#include <string.h>

int xmlparse();
int dtdparse();
int xslparse();
extern FILE * xmlin;
extern int xmldebug;
extern FILE * dtdin;
extern int dtddebug;
extern char * nomdtd;
extern FILE * xslin;
extern int xsldebug;

int main(int argc, char **argv)
{
	char nomFicXml[20];
	char nomFicDtd[20];
	char nomFicXsl[20];
	FILE * fid;
	int err;
	
	
	strcpy(nomFicXml, "./rap1.xml"); 
	fid = fopen(nomFicXml, "r");
	if (!nomFicXml){
		printf("Erreur d'ouverture du fichier XML\n");
		return -1;
	}
	xmlin = fid;
	//xmldebug = 1; // pour enlever l'affichage de l'exécution du parser, commenter cette ligne
	err = xmlparse();
	fclose(fid);
	if (err != 0) printf("XML Parse ended with %d error(s)\n", err);
  	else  printf("XML Parse ended with success\n", err);
	
	
	
	
	
	strcpy(nomFicDtd, "./rap1.dtd");
	fid = fopen(nomFicDtd, "r");
	if (!nomFicDtd){
		printf("Erreur d'ouverture du fichier XML\n");
		return -1;
	}
	dtdin = fid;
  //dtddebug = 1; // pour désactiver l'affichage de l'exécution du parser LALR, commenter cette ligne
	err = dtdparse();
	if (err != 0) printf("DTD Parse ended with %d error(s)\n", err);
        else  printf("DTD Parse ended with success\n", err);
	
	
	
	strcpy(nomFicXsl, "./rap1.xsl"); 
	fid = fopen(nomFicXsl, "r");
	if (!nomFicXsl){
		printf("Erreur d'ouverture du fichier XSL\n");
		return -1;
	}
	xslin = fid;
	//xsldebug = 1; // pour enlever l'affichage de l'exécution du parser, commenter cette ligne
	err = xslparse();
	fclose(fid);
	if (err != 0) printf("XSL Parse ended with %d error(s)\n", err);
  	else  printf("XSL Parse ended with success\n", err);
	
	
	
  return 0;
}
