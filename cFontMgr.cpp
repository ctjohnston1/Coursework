/*
== == == == == == == == =
cFontMgr.h
- Header file for class definition - SPECIFICATION
- Header file for the cFontMgr class
== == == == == == == == =
*/

#include "cFontMgr.h"

cFontMgr* cFontMgr::pInstance = NULL;

/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
cFontMgr* cFontMgr::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cFontMgr();
	}
	return cFontMgr::pInstance;
}

/*
=================================================================================
Constructor
=================================================================================
*/
cFontMgr::cFontMgr()
{

}

cFontMgr::~cFontMgr()							// Destructor.
{
	deleteFont();
}
void cFontMgr::addFont(LPCSTR fontName, LPCSTR fileName, int fontSize)  // add font to the Font collection
{
	if (!getFont(fontName))//checks if the current value returned for getFont function equals the name passed in (it allows more than one font to be added)
	{
		cFont * newFont = new cFont(fileName, fontSize);//new font  with specified name and size
		gameFonts.insert(make_pair(fontName, newFont));
	}
}

cFont* cFontMgr::getFont(LPCSTR fontName)				// return the font for use
{
	map<LPCSTR, cFont*>::iterator theFont = gameFonts.find(fontName);
	if (theFont != gameFonts.end())
	{
		return theFont->second;
	}
	else
	{
		return NULL;
	}
}

void cFontMgr::deleteFont()								// delete font.
{
	for (map<LPCSTR, cFont*>::const_iterator theFont = gameFonts.begin(); theFont != gameFonts.end(); theFont++)
	{
		delete theFont->second;
	}
}
