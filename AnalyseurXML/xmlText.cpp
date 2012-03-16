#ifndef XMLTEXT_H
#define XMLTEXT_H

#include "xmlText.h"
#include "xmlNode.h"
#include <string>

using namespace std;

class xmlText : public xmlNode{
	
	private
	
	public
	
	xmlText::Text(std::string content)
	{
		text = content;
	}


	xmlText::~Text();
	{
	}	

	string xmlText::getText()
	{
		return text;
	}
};

#endif
