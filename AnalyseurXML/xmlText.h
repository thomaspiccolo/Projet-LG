#ifndef XMLTEXT_H
#define XMLTEXT_H

using namespace std;

class xmlText : public xmlNode{
	private
	
	string text;
		
	public
	
	xmlText();
	string getText(); 
}

#endif
