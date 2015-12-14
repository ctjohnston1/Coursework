/*
==================================================================================
cSphere.cpp
==================================================================================
*/

#include "cSphere.h"


cSphere::cSphere()
{
	setRotAngle(0.0f);
}

cSphere::cSphere(GLdouble dRadius, GLint dSlices, GLint dStacks)//constructor passes parameters that will be assigned to variables
{
	setRotAngle(0.0f);//rotation angle set to 0
	sRadius = dRadius;
	sSlices = dSlices;
	sStacks = dStacks;
}

void cSphere::render(float rotAngle)//renders the sphere
{
	glMatrixMode(GL_MODELVIEW);//loads the view matrix
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);//enables texture 2D, normalise and colour material
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);


	glBindTexture(GL_TEXTURE_2D, m_TextureID);//binds the texture

	glTranslatef(m_Position.x, m_Position.y, m_Position.z);//moves the sphere to the place defined
	glRotatef(90.0f, 1.0f, 0.0f, 0.0f); // Rotate Sphere to take account of gluSphere caps
	glRotatef(getRotAngle(), 0, 0, 1);	// Rotation is now on z rather than Y to make sphere spin

	gluSphere(quad, sRadius, sSlices, sStacks);//created the sphere

	glDisable(GL_NORMALIZE);//deactivates texture 2D, normalise and colour material
	glDisable(GL_COLOR_MATERIAL);
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
}

void cSphere::initialise(cTexture theTexture)//initialised the sphere
{
	quad = gluNewQuadric();
	//preps the texture onto the sphere
	gluQuadricDrawStyle(quad, GLU_FILL);
	gluQuadricNormals(quad, GLU_SMOOTH);
	gluQuadricTexture(quad, GL_TRUE);
	//binds the texture
	glBindTexture(GL_TEXTURE_2D, theTexture.getTexture());

}

void cSphere::initialise(GLint theTextureID, glm::vec3 thePosition, glm::vec3 theTranslation)//initialises the sphere with the parameters passed through it
{
	quad = gluNewQuadric();
	m_TextureID = theTextureID;
	m_Position = thePosition;
	m_Translation = theTranslation;
	//preps the texture onto the sphere
	gluQuadricDrawStyle(quad, GLU_FILL);
	gluQuadricNormals(quad, GLU_SMOOTH);
	gluQuadricTexture(quad, GL_TRUE);
	//binds the texture
	glBindTexture(GL_TEXTURE_2D, m_TextureID);

}