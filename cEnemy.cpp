#include "cEnemy.h"

cEnemy::cEnemy() : cModel()//enemy is inherant with model ie cEnemy is a type if cModel
{
	
}

void cEnemy::randomise()//randomisation function
{
	if (rand() % 2 == 0) // if (randomize in the ranger of 0 to 2) is equal to 0 then
	{
		cModel::m_mdlPosition.x = -PLAYFIELDX; //models x position = -PLAYFIELDX wich is 100.0f in GameConstant.h
	}
	else
	{
		cModel::m_mdlPosition.x = PLAYFIELDX;//models x position = PLAYFIELDX wich is 100.0f in GameConstant.h
	}
	cModel::m_mdlPosition.y = 0.0f;//model y postion is 0
	cModel::m_mdlPosition.z = (rand() / (float)RAND_MAX) * 300.0f;   // random number as a float between 0 & 1
	cModel::m_mdlRotation = (rand() / (float)RAND_MAX) * 2 * 3.14f;//random number between 1&0 multiplies by 2 and then by pie which in radians is 180 degrees
	cModel::m_mdlDirection.x = -(float)glm::sin(cModel::m_mdlRotation);//maths for its direction on x axis
	cModel::m_mdlDirection.z = (float)glm::cos(cModel::m_mdlRotation);//maths for its direction on y axis
	cModel::m_mdlSpeed = m_EnemyMinSpeed + rand() / (float)RAND_MAX * m_EnemyMaxSpeed;//sets the model speed
	cModel::m_IsActive = true;//sets its activity to true
}

void cEnemy::update(float elapsedTime)//update funciton passing in the elapsed time
{
	cModel::m_mdlPosition += cModel::m_mdlDirection * cModel::m_mdlSpeed * elapsedTime;//movement utilizing on the elapsed time
	if (cModel::m_mdlPosition.x > PLAYFIELDX)
		cModel::m_mdlPosition.x -= 2 * PLAYFIELDX;
	if (cModel::m_mdlPosition.x < -PLAYFIELDX)
		cModel::m_mdlPosition.x += 2 * PLAYFIELDX;
	if (cModel::m_mdlPosition.z > PLAYFIELDZ)
		cModel::m_mdlPosition.z -= 2 * PLAYFIELDZ;
	if (cModel::m_mdlPosition.z < -PLAYFIELDZ)
		cModel::m_mdlPosition.z += 2 * PLAYFIELDZ;
}

cEnemy::~cEnemy()//deconstructor
{

}

