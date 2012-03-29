#include "xmlText.h"
#include "xmlNode.h"
#include <string>
#include <iostream>

using namespace std;

xmlText::xmlText(std::string content)
{
	text = content;
}


xmlText::~xmlText()
{
}	

string xmlText::getText()
{
	return text;
}


void xmlText::display()
{
	cout << text << endl;	
}
