/*
==========================================================================
ccCamera.h
==========================================================================
*/

#include "cCamera.h"

cCamera::cCamera()//CAMERA CONSTRUCTOR
{
	//the private variables
	m_viewPort = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);//view port
	m_cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);//position
	m_ProjectionMatrix = glm::mat4(1.0);//projection matrix
	m_camViewMatrix = glm::mat4(1.0);//view matrix
}


cCamera::cCamera(int screenWidth, int screenHeight)//constructor that deals with the screen width and height being passed into it
{
	m_viewPort = glm::vec4(0, 0, screenWidth, screenHeight);
	m_cameraPos = glm::vec3(0.0f, 0.0f, 0.0f);
	m_ProjectionMatrix = glm::mat4(1.0);
	m_camViewMatrix = glm::mat4(1.0);
}

cCamera::~cCamera()//deconstructor
{
	
}

void cCamera::setTheViewPort(int x, int y, int width, int height)//sets the view port with the passed values
{
	m_viewPort = glm::vec4(x, y, width, height);
	glViewport(x, y, width, height);//sets the viewport
}

const glm::vec4 cCamera::getTheViewPort()
{
	return m_viewPort;//returns value of private variabel m_viewPort
}

void cCamera::setTheProjectionMatrix(float fov, float aspectRatio, float nearCP, float farCP)//sets the projection matrix of camera
{
	m_ProjectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearCP, farCP);
}

void cCamera::setTheCameraPos(glm::vec3 pos)//sets the position of the camera
{
	m_cameraPos = pos;
}

glm::vec3 cCamera::getTheCameraPos()//returns the camera postion
{
	return m_cameraPos;
}

void cCamera::setTheCameraUpVector(glm::vec3 camPosUpVec)//sets the up vector of camera
{
	m_cameraUpVector = camPosUpVec;
}

glm::vec3 cCamera::getTheCameraUpVector()//returns the up vector of the camera
{
	return m_cameraUpVector;
}

void cCamera::setTheCameraLookAt(glm::vec3 camLookAt)//sets the angle of the camera
{
	m_cameraLookAt = camLookAt;
}

glm::vec3 cCamera::getTheCameraLookAt()//returns the angle of the camera
{
	return m_cameraLookAt;
}

void cCamera::setTheCameraDirection()//sets the direction of the camera
{
	m_cameraDirection = glm::normalize(m_cameraPos - m_cameraLookAt);
}

glm::vec3 cCamera::getTheCameraDirection()//returns the dirction of the camera
{
	return m_cameraDirection;
}

void cCamera::setTheCameraStrafe()//sets the camera Straffe
{
	m_cameraStrafe = glm::normalize(glm::cross(m_cameraUpVector, m_cameraDirection));
}

glm::vec3 cCamera::getTheCameraStrafe()//returns the camera Straffe
{
	return m_cameraStrafe;
}

void cCamera::setTheCameraAspectRatio(GLfloat width, GLfloat height)//sets the aspect ration
{
	m_AspectRatio = width/height;
}

GLfloat cCamera::getTheCameraAspectRatio()//returns the aspect ratio
{
	return m_AspectRatio;
}

glm::mat4 cCamera::getTheProjectionMatrix()//returns the projection matrix
{
	return m_ProjectionMatrix;
}

glm::mat4 cCamera::getTheViewMatrix()//returns the view matrix
{
	return m_camViewMatrix;
}

void cCamera::setCamViewMatrix()//sets the view matrix
{
	m_camViewMatrix = glm::lookAt(m_cameraPos, m_cameraLookAt, m_cameraUpVector);
}

glm::mat4 cCamera::getCamViewMatrix()//returns the view matrix
{
	return m_camViewMatrix;
}

void cCamera::update()
{
	setTheCameraDirection();
	setTheCameraStrafe();
	setTheCameraUpVector(glm::cross(m_cameraDirection, m_cameraStrafe));
	setTheProjectionMatrix(45.0f, getTheCameraAspectRatio(), 0.1f, 300.0f);
	setCamViewMatrix();
}
