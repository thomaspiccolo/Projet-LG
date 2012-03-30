#include "xmlElement.h"
#include "xmlTransform.h"
#include "commun.h"
#include "Dtd.h"

#include <string>
#include <iostream>
#include <fstream>

//erreurs de parsage
#define NOERROR 0
#define XMLERROR 1
#define DTDERROR 2
#define XSLERROR 3

//type de parsage
#define ALLPARSE 0
#define XMLONLYPARSE 1
#define XMLDTDPARSE 2

using namespace std;

extern xmlElement * root;
extern xmlElement * current;
extern Dtd * unDtd;


int xmlparse();
int dtdparse();
extern FILE * xmlin;
extern int xmldebug;
extern FILE * dtdin;
extern int dtddebug;
extern char * nomdtd;
extern FILE * xslin;
extern int xsldebug;

int xmlTest();
int docparse(char* fichierXml, int typeAppel);
void afficherResultat(int error, int attendu);

int main(int argc, char **argv)
{
	#ifdef DEBUGTEST
		xmlTest();
	#else
		char error[3];
		docparse("rap1.xml",ALLPARSE);
	#endif
	return 0;
}

//lance les tests xml
int xmlTest()
{
	int error;
	char typeError [10];

	//Test 1
	cout << "========================================" << endl;
	cout << "==============Test 1====================" << endl << endl;
	cout << "Test d'un fichier xml bien formé" << endl;
	getchar();
	error= docparse("tests/test1-0.xml", XMLONLYPARSE);
	afficherResultat(error, NOERROR);
	getchar();
	

	//Test 2
	cout << "========================================" << endl;
	cout << "==============Test 2====================" << endl << endl;
	cout << "Test d'un fichier xml avec la balise Doctype mal fermée" << endl;
	getchar();
	error= docparse("tests/test1-1.xml", XMLONLYPARSE);
	afficherResultat(error, XMLERROR);
	getchar();

	//Test 3
	cout << "========================================"  << endl;
	cout << "==============Test 3====================" << endl << endl;
	cout << "Test d'un fichier xml avec la balise qui sert de racine mal fermée" << endl;
	getchar();
	error= docparse("tests/test1-2.xml", XMLONLYPARSE);
	afficherResultat(error, XMLERROR);
	getchar();
	
	//Test 4
	cout << "========================================"  << endl;
	cout << "==============Test 4====================" << endl << endl;
	cout << "Test d'un fichier xml contenant une balise mal fermée" << endl;
	getchar();
	error= docparse("tests/test1-3.xml", XMLONLYPARSE);
	afficherResultat( error, XMLERROR);
	getchar();

	//Test 5
	cout << "========================================"  << endl;
	cout << "==============Test 5====================" << endl << endl;
	cout << "Test d'un fichier xml contenant une balise mal ouverte" << endl;
	error= docparse("tests/test1-4.xml", XMLONLYPARSE);
	afficherResultat(error, XMLERROR);
	getchar();

	//Test 6
	cout << "========================================"  << endl;
	cout << "==============Test 6====================" << endl << endl;
	cout << "Test d'un fichier xml contenant un attribut à valeur incorrecte (guillemet à droite manquant)" << endl;
	getchar();
	error= docparse("tests/test1-5.xml", XMLONLYPARSE);
	afficherResultat(error, XMLERROR);
	getchar();	

	//Test 7
	cout << "========================================" << endl;
	cout << "==============Test 7====================" << endl << endl;
	cout << "Test d'un fichier xml contenant un attribut à valeur incorrecte (guillemet à gauche manquant)" << endl;
	getchar();
	error= docparse("tests/test1-6.xml", XMLONLYPARSE);
	afficherResultat(error, XMLERROR);
	getchar();
	
	//Test 8
	cout << "========================================"  << endl;
	cout << "==============Test 8====================" << endl << endl;
	cout << "Test d'un fichier xml contenant un attribut sans valeur" << endl;
	getchar();
	error= docparse("tests/test1-7.xml", XMLONLYPARSE);
	afficherResultat(error, XMLERROR);
	getchar();	

	return 0;
}

void afficherResultat(int error, int attendu)
{
	cout << "========================================" << endl;
	cout << "==============Résultat du Test==========" << endl;
	cout << "Résulat obtenu: " << error << endl;
	if(error == NOERROR)
	{	
		cout << "Pas d'erreur de Parsing" << endl;
	}
	
	else if(error== XMLERROR)
	{
		cout << "Erreur de Parsing XML " << endl;
	}
	else if(error== DTDERROR)
	{
		cout << "Erreur de Parsing DTD " << endl;
	}
	else if(error== XSLERROR)
	{
		cout << "Erreur de Parsing XSL " << endl;
	}

	cout << "Résulat attendu:";
	if(attendu == NOERROR)
	{	
		cout << "Pas d'erreur de Parsing" << endl;
	}
	else if(attendu== XMLERROR)
	{
		cout << "Erreur de Parsing XML " << endl;
	}
	else if(attendu== DTDERROR)
	{
		cout << "Erreur de Parsing DTD " << endl;
	}
	else if(attendu== XSLERROR)
	{
		cout << "Erreur de Parsing XSL " << endl;
	}
	
	if (error == attendu)
	{
		cout << "Le Test a été passé avec succès" << endl;
	}

	if(error != attendu)
	{
		cout << "Le Test a été passé avec succès" << endl;
	}
}

int docparse(char* fichierXml, int typeAppel)
{
	
	cout << "========================================" << endl;
	cout << "=================Analyse================" << endl;
	cout << "========================================" << endl;
	xmlElement * xmlTree;
	xmlElement * xslTree;
	char nomFicXml[40];
	char nomFicDtd[40];
	char nomFicXsl[40];
	
	FILE * fid;
	int err;

	strcpy(nomFicXml, fichierXml);
	
	fid = fopen(nomFicXml, "r");
	if (!fid){
		printf("Erreur d'ouverture du fichier XML\n");
		cout << "========================================" << endl;
		cout << "=========Fin de l'Analyse===============" << endl;
		cout << "========================================" << endl;
		return -1;
	}
	xmlin = fid;
	//xmldebug = 1; // pour enlever l'affichage de l'exécution du parser, commenter cette ligne
	err = xmlparse();
	fclose(fid);
	if (err != 0) 
	{
		printf("XML Parse ended with %d error(s)\n", err);
		cout << "========================================" << endl;
		cout << "=========Fin de l'Analyse===============" << endl;
		cout << "========================================" << endl;
		return XMLERROR;
	}
  	else  printf("XML Parse ended with success\n", err);
	xmlTree = root;

	if(typeAppel==XMLONLYPARSE)
	{
			cout << "========================================" << endl;
			cout << "=========Affichage du XML===============" << endl;
			cout << "========================================" << endl;
			xmlTree->display();
			cout << "========================================" << endl;
			cout << "=========Fin de l'Affichage=============" << endl;
			cout << "========================================" << endl;
			getchar();

		cout << "========================================" << endl;
		cout << "=========Fin de l'Analyse===============" << endl;
		cout << "========================================" << endl;
		return NOERROR;
	}
	
	strcpy(nomFicDtd, "./rap1.dtd");
	fid = fopen(nomFicDtd, "r");
	if (!nomFicDtd){
		printf("Erreur d'ouverture du fichier DTD\n");
		cout << "========================================" << endl;
		cout << "=========Fin de l'Analyse===============" << endl;
		cout << "========================================" << endl;
		return -1;
	}
	dtdin = fid;
  //dtddebug = 1; // pour d¨¦sactiver l'affichage de l'ex¨¦cution du parser LALR, commenter cette ligne
	err = dtdparse();
  	if (err != 0) 
  		printf("DTD Parse ended with %d error(s)\n", err);
	else  
		printf("DTD Parse ended with success\n", err);
	
	if(typeAppel==XMLDTDPARSE)
	{
		cout << "========================================" << endl;
		cout << "=========Fin de l'Analyse===============" << endl;
		cout << "========================================" << endl;
		return NOERROR;
	}
	
	strcpy(nomFicXsl, "./rap1.xsl"); 
	fid = fopen(nomFicXsl, "r");
	if (!fid){
		printf("Erreur d'ouverture du fichier XSL\n");
		cout << "========================================" << endl;
		cout << "=========Fin de l'Analyse===============" << endl;
		cout << "========================================" << endl;
		return -1;	
	}
	xmlin = fid;
	//xsldebug = 1; // pour enlever l'affichage de l'exécution du parser, commenter cette ligne
	err = xmlparse();
	fclose(fid);
	if (err != 0) printf("XSL Parse ended with %d error(s)\n", err);
  	else  printf("XSL Parse ended with success\n", err);
	xslTree = root;
	
	

	xmlElement * htmlOutput = find(xmlTree,xslTree);	
	ofstream myFile;
  	myFile.open ("outputHtml.html", ios::out);
  	myFile << htmlOutput->getChildElement(0)->write();
  	myFile.close();
	cout << "Ecriture de la sortie HTML effectuée" << endl;


	cout << "========================================" << endl;
	cout << "=========Affichage du XML===============" << endl;
	cout << "========================================" << endl;
	xmlTree->display();
	cout << "========================================" << endl;
	cout << "=========Fin de l'Affichage=============" << endl;
	cout << "========================================" << endl;
	getchar();
	cout << "========================================" << endl;
	cout << "=========Affichage du DTD===============" << endl;
	cout << "========================================" << endl;
	unDtd->Display();
	cout << "========================================" << endl;
	cout << "=========Fin de l'Affichage=============" << endl;
	cout << "========================================" << endl;
	getchar();
	cout << "========================================" << endl;
	cout << "=========Affichage du XSL===============" << endl;
	cout << "========================================" << endl;
	xslTree->display();
	cout << "========================================" << endl;
	cout << "=========Fin de l'Affichage=============" << endl;
	cout << "========================================" << endl;
	getchar();
	cout << "========================================" << endl;
	cout << "=========Affichage du HTML==============" << endl;
	cout << "========================================" << endl;
	htmlOutput->getChildElement(0)->display();
	cout << "========================================" << endl;
	cout << "=========Fin de l'Affichage=============" << endl;
	cout << "========================================" << endl;
	
	cout << "========================================" << endl;
	cout << "=========Fin de l'Analyse===============" << endl;
	cout << "========================================" << endl;

	return NOERROR;
}
