#include "windowOGL.h"

windowOGL::windowOGL()
{

}

bool windowOGL::initOGL(int width, int height)//initiate ogl function
{
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glClearStencil(0);                          // clear stencil buffer
	glClearDepth(1.0f);                         // 0 is near, 1 is far
	glDepthFunc(GL_LEQUAL);
	onResize(width, height);

    //Return success
    return true;
}

void windowOGL::renderOGL(float rotAngle)//render ogl function
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear buffers
    glLoadIdentity(); //load the identity matrix
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //controls the interpretation of polygons for rasternization

}

void windowOGL::shutdown()//shutdown function
{

}

void windowOGL::onResize(int width, int height) //on resize function
{
    glViewport(0, 0, width, height); //sets view

    glMatrixMode(GL_PROJECTION); //specifies the projection matrix
    glLoadIdentity();//load current matrix

    gluPerspective(45.0f, float(width) / float(height), 1.0f, 100.0f); //sets the perspective

    glMatrixMode(GL_MODELVIEW); //specifies the modelview matrix

    glLoadIdentity(); //loads matrix
}

void windowOGL::setOrtho2D(int width, int height) //sets ortho2d function
{
	glDisable(GL_DEPTH_TEST); //dissables the depth test
	glDisable(GL_LIGHTING); //dissables the lighting
	glViewport(0, 0, width, height);//sets viewport with parameter values
	glMatrixMode(GL_PROJECTION);//specifies projection matrix
	glLoadIdentity();//loads matrix
	glOrtho(0.0, width, height, 0.0, 0.0, -1.0); //multiply current matrix with orthographic matrix
	glMatrixMode(GL_MODELVIEW); //specifies modelview matrix
	glLoadIdentity(); //loads matrix
}

void windowOGL::setProjection3D(int width, int height)//set projection for 3D funtion
{
	onResize(width, height); //calls onResize passing the parameters width and height.
}