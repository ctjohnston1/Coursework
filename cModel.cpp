#include "cModel.h"

cModel::cModel()//constructors
{
	//private variables
	m_mdlPosition = glm::vec3(0.0f, 0.0f, 0.0f);
	m_mdlRotation = 0.0f;
	m_mdlDirection = glm::vec3(0.0f, 0.0f, 0.0f);
	m_mdlSpeed = 0.0f;
	m_IsActive = false;
	m_mdlScale = glm::vec3(1.0f, 1.0f, 1.0f);
	m_Dimensions.s_mdldepth = 0.0f;
	m_Dimensions.s_mdlheight = 0.0f;
	m_Dimensions.s_mdlWidth = 0.0f;
	m_mdlRadius = m_Dimensions.s_mdldepth / 2;
	m_TextureID = 0;
}

// +++++++++++++++++++++++++++++++++++++++++++++
// Setters
// +++++++++++++++++++++++++++++++++++++++++++++

void cModel::setPosition(glm::vec3 mdlPosition)//sets position
{
	m_mdlPosition = mdlPosition;
}

void cModel::setRotation(GLfloat mdlRotation)//sets rotation
{
	m_mdlRotation = mdlRotation;
}

void cModel::setDirection(glm::vec3 mdlDirection)//sets direction
{
	m_mdlDirection = mdlDirection;
}

void cModel::setSpeed(float mdlSpeed)//sets speed
{
	m_mdlSpeed = mdlSpeed;
}

void cModel::setIsActive(bool mdlIsActive)//sets active value
{
	m_IsActive = mdlIsActive;
}

void cModel::setMdlDimensions(mdlDimensions mdlDims)//sets the models dimentions
{
	m_Dimensions = mdlDims;
	m_mdlRadius = m_Dimensions.s_mdldepth / 2;
}

void cModel::setMdlRadius(float mdlRadius)//sets the models radius
{
	m_mdlRadius = mdlRadius;
}

void cModel::setScale(glm::vec3 mdlScale)//sets the models scale
{
	m_mdlScale = mdlScale;
}

// +++++++++++++++++++++++++++++++++++++++++++++
// Getters
// +++++++++++++++++++++++++++++++++++++++++++++

glm::vec3 cModel::getPosition()//returns the positon
{
	return m_mdlPosition;
}

GLfloat cModel::getRotation()//returns the rotation
{
	return m_mdlRotation;
}

glm::vec3 cModel::getDirection()//returns the direction
{
	return m_mdlDirection;
}

float cModel::getSpeed()//returns the speed
{
	return m_mdlSpeed;
}

bool cModel::isActive()//returns the activty value
{
	return m_IsActive;
}

mdlDimensions cModel::getMdlDimensions()//returns the model dimentions
{
	return m_Dimensions;
}

float cModel::getMdlRadius()//returns the model radius
{
	return m_mdlRadius;
}

glm::vec3 cModel::getScale()//returns the scale value
{
	return m_mdlScale;
}

void cModel::setTextureID(GLuint theTextureID)//sets the textureID by passing in a value
{
	m_TextureID = theTextureID;
}
//initialises model
void cModel::initialise(glm::vec3 mdlPosition, GLfloat mdlRotation, glm::vec3 mdlScale, glm::vec3 mdlDirection, float mdlSpeed, bool mdlIsActive)
{
	//sends passed variables to corresponding functions
	setPosition(mdlPosition);
	setRotation(mdlRotation);
	setScale(mdlScale);
	setDirection(mdlDirection);
	setSpeed(mdlSpeed);
	setIsActive(mdlIsActive);
	//zeros the dimentions of the model
	m_Dimensions.s_mdldepth = 0.0f;
	m_Dimensions.s_mdlheight = 0.0f;
	m_Dimensions.s_mdlWidth = 0.0f;
	m_mdlRadius = m_Dimensions.s_mdldepth / 2;
	//gets results from the functions and acts upon it
	glm::vec3 mdlPos = getPosition();
	GLfloat mdlRot = getRotation();
	glRotatef(mdlRot, 0.0f, 1.0f, 0.0f);
	glTranslatef(mdlPos.x,mdlPos.y,mdlPos.z);
}

bool cModel::SphereSphereCollision(glm::vec3 mdlPosition, float mdlRadius)//collision detection model
{
	const float distSq = lengthSQRD(m_mdlPosition - mdlPosition);

	const float sumRadius = (m_mdlRadius + mdlRadius);

	if (distSq < sumRadius * sumRadius)
	{
		return true; // Collision
	}
	return false; // No Collision
}

float cModel::lengthSQRD(glm::vec3 mdlLength)
{
	return (mdlLength.x * mdlLength.x) + (mdlLength.y * mdlLength.y) + (mdlLength.z * mdlLength.z);
}

/*
=================================================================
Attach the input manager to the sprite
=================================================================
*/
void cModel::attachInputMgr(cInputMgr* inputMgr)
{
	m_InputMgr = inputMgr;
}
/*
=================================================================
Attach the sound manager to the sprite
=================================================================
*/
void cModel::attachSoundMgr(cSoundMgr* soundMgr)
{
	m_SoundMgr = soundMgr;
}

cModel::~cModel()//deconstructor
{

}
