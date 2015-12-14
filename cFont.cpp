/*
==========================================================================
cFont.cpp
==========================================================================
*/
#pragma warning ( disable : 4996 )
#include "cFont.h"
using namespace std;

/*
==========================================================================
Default Constructor
==========================================================================
*/
cFont::cFont()//constructor
{
	theFont = NULL;
}
/*
==========================================================================
Overloaded constructor
==========================================================================
*/
cFont::cFont(LPCSTR fontFileName, int fontSize)//constructor
{
	theFont = new FTTextureFont(fontFileName);//passes in the font filename
	//in the event that the font is NULL or the font size is too big/small and cant be matched up with the appropriate font image
	//pass these messages and delete the attempted font
	if (theFont == NULL)
	{
		MessageBox(NULL, "Unable to create the required Font!", "An error occurred", MB_ICONERROR | MB_OK);
		delete theFont;
	}

	if (!theFont->FaceSize(fontSize))
	{
		MessageBox(NULL, "Unable to set desired size for Font!", "An error occurred", MB_ICONERROR | MB_OK);
		delete theFont;
	}
}

/*
==========================================================================
Destructor
==========================================================================
*/
cFont::~cFont()//deconstructor
{
	delete theFont;//delete the font
}
/*
==========================================================================
get the pointer to the font
==========================================================================
*/
FTFont* cFont::getFont()//returns the font
{
	return theFont;
}

/*
==========================================================================
Render the text using the desired font
==========================================================================
*/
void cFont::printText(LPCSTR text, FTPoint textPos)//renders the font by passing in the desired text and its desired position
{
	glPushMatrix(); //push

	glTranslatef(textPos.X(), textPos.Y(), 0 );//move to position
	// glRotatef(180,1, 0, 0); // Will work too
	glScalef(1, -1, 1);//set the size
	glColor3f(0.0f, 255.0f, 0.0f);//set the colour 
	theFont->Render(text);//render words

	glPopMatrix(); //pop
}

void cFont::printText(LPCSTR text, FTPoint textPos, colour3f textColour)//renders the font by passing in the text, position and the colour
{
	glPushMatrix();//push

	glTranslatef(textPos.X(), textPos.Y(), 0);//position it
	glScalef(1, -1, 1);//scale it
	glColor3f(textColour.r, textColour.g, textColour.b);//colour it
	theFont->Render(text);//render the text

	glPopMatrix();//pop
}
