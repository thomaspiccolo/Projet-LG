#ifndef XMLTEXT_H
#define XMLTEXT_H

#include "xmlNode.h"
#include <string>

class xmlText : public xmlNode{
	private:
	
	std::string text;
		
	public:
	
	xmlText(std::string content);
	~xmlText();
	std::string getText(); 
};

#endif
