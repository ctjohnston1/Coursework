/*
==================================================================================
cStarfield.cpp
==================================================================================
*/

#include "cStarfield.h"


cStarfield::cStarfield()//constructor of starfield
{
	//variables that are public
	srand((unsigned)time(NULL));
	setRotAngle(0.0f);
	glGetFloatv(GL_ALIASED_POINT_SIZE_RANGE, m_AliasedPointSizes);
	//private variables
	m_NumStars = 1000;
	m_TextureID = 0;
	m_FieldVolume = glm::vec3(1.0f,1.0f,1.0f);
	m_StarPos = glm::vec3(0.0f, 0.0f, 0.0f);
	//makes the star field
	generateStarField();
}

cStarfield::cStarfield(GLint theTextureID, glm::vec3 theFieldVolume)//construct star fied with a texture and vec3 value being passed into it
{
	//public variables
	srand((unsigned)time(NULL));
	setRotAngle(0.0f);
	glGetFloatv(GL_ALIASED_POINT_SIZE_RANGE, m_AliasedPointSizes);
	//private variables
	m_NumStars = 1000;
	m_TextureID = theTextureID;
	m_FieldVolume = theFieldVolume;
	m_StarPos = glm::vec3(0.0f, 0.0f, 0.0f);
	//make the star field
	generateStarField();
}

void cStarfield::render(float rotAngle)//render the star field
{
	glMatrixMode(GL_MODELVIEW);//selects modelview matrix
	glPushMatrix();//pushes the matrix

	glEnable(GL_TEXTURE_2D);//enables texturing in 2D
	glBindTexture(GL_TEXTURE_2D, m_TextureID);//binds texture 
	glEnable(GL_POINT_SPRITE);//turns on point sprites
	glTexEnvi(GL_POINT_SPRITE, GL_COORD_REPLACE, GL_TRUE);//replaces points with texture coordinates
	glEnable(GL_BLEND);//turns blend on
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //plends the points
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glDepthMask(GL_FALSE);
	glPointSize(36.0f);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);//sets colour rgba
	glm::vec3 pointInSpace;//moves them
	glBegin(GL_POINTS);
	for (int loop = 0; loop < m_StarField.size(); loop++)//creates the stars for the field witht the defined size
	{ 	
		pointInSpace = m_StarField.at(loop);
		glVertex3f(pointInSpace.x, pointInSpace.y, pointInSpace.z);
	}
	glEnd();//end of process

	glDisable(GL_POINT_SPRITE);//deactivate what you activated initially
	glDisable(GL_TEXTURE_2D);
	glDepthMask(GL_TRUE);
	glPopMatrix();//pop resulting matrix
}

void cStarfield::initialise(cTexture theTexture)//initialise starfied with passed in texture
{
	srand((unsigned)time(NULL));
	glBindTexture(GL_TEXTURE_2D, theTexture.getTexture());//bind
}

void cStarfield::initialise(GLint theTextureID, glm::vec3 theFieldVolume)//intialise starfield with passed in texture and vec3 value
{
	srand((unsigned)time(NULL));
	m_TextureID = theTextureID;
	m_FieldVolume = theFieldVolume;

	glBindTexture(GL_TEXTURE_2D, m_TextureID);//bind

}

void cStarfield::generateStarField()//make the starfield
{
	// generate starfield

	for (int loop = 0; loop < m_NumStars; loop++)//loop to the specificly defined number of stars
	{
		if (rand() % 3 == 0)//if random = 0 when the value can be anywhere between 0 and 3 
		{
			m_StarPos.x = -(rand() % (int)m_FieldVolume.x);//star in this position x axis
		}
		else
		{
			m_StarPos.x = (rand() % (int)m_FieldVolume.x);//star in this position x axis
		}
		if (rand() % 3 == 1)
		{
			m_StarPos.y = -(rand() % (int)m_FieldVolume.y);//star in this position y axis
		}
		else
		{
			m_StarPos.y = (rand() % (int)m_FieldVolume.y);//star in this position y axis
		}
		if (rand() % 3 == 2)
		{
			m_StarPos.z = -(rand() % (int)m_FieldVolume.z);//star in this position z axis
		}
		else
		{
			m_StarPos.z = (rand() % (int)m_FieldVolume.z);//star in this position z axis
		}
		m_StarField.push_back(glm::vec3(m_StarPos.x, m_StarPos.y, m_StarPos.z));//push the generated star onto the scene
	}
}