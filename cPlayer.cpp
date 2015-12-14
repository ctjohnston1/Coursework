#include "cPlayer.h"


cPlayer::cPlayer() : cModel()//cPlayer inherits from cModel ie cPlayer is a type of cModel
{

}

void cPlayer::attachInputMgr(cInputMgr* inputMgr)//attaches input manager to the player
{
	m_InputMgr = inputMgr;
}

void cPlayer::update(float elapsedTime)//updates player
{
	if (m_InputMgr->isKeyDown(VK_RIGHT))//right arrow key
	{
		rotationAngle += 5.0f;//rotate
	}
	if (m_InputMgr->isKeyDown(VK_LEFT))//left arrow key
	{
		rotationAngle -= 5.0f; //rotate
	}
	if (m_InputMgr->isKeyDown(VK_UP))//up arrow key
	{
		translationZ += 5.0f;//translate
	}
	if (m_InputMgr->isKeyDown(VK_DOWN))//down arrow key
	{
		translationZ -= 5.0f;//translate
	}

	if (m_InputMgr->isKeyDown(VK_SPACE))//spacebar pressed
	{
		//set the position of the laser that will be fired
		glm::vec3 mdlLaserDirection;
		mdlLaserDirection.x = -(float)glm::sin(glm::radians(this->getRotation()));
		mdlLaserDirection.y = 0.0f;
		mdlLaserDirection.z = (float)glm::cos(glm::radians(this->getRotation()));
		mdlLaserDirection *= -1;

		// Add new bullet sprite to the vector array
		theTardisLasers.push_back(new cLaser);
		int numLasers = theTardisLasers.size() - 1;
		theTardisLasers[numLasers]->setDirection(mdlLaserDirection);
		theTardisLasers[numLasers]->setRotation(0.0f);
		theTardisLasers[numLasers]->setScale(glm::vec3(1, 1, 1));
		theTardisLasers[numLasers]->setSpeed(5.0f);
		theTardisLasers[numLasers]->setPosition(this->getPosition() + mdlLaserDirection);
		theTardisLasers[numLasers]->setIsActive(true);
		//theTardisLasers[numLasers]->setMdlDimensions(theLaser.getModelDimensions());
		theTardisLasers[numLasers]->update(elapsedTime);
		// play the firing sound
energy = energy - 1; //subtract from energy value
		
m_SoundMgr->getSnd("Blaster")->playAudio(AL_TRUE); //will play new blaster sound 

		
		
	}

	/*
	==============================================================
	| Check for collisions
	==============================================================
	*/
	for (vector<cLaser*>::iterator laserIterartor = theTardisLasers.begin(); laserIterartor != theTardisLasers.end(); ++laserIterartor)//as long as the laser is active proceed further
	{
		(*laserIterartor)->update(elapsedTime);//update laster with elapsed time
		for (vector<cEnemy*>::iterator enemyIterator = theEnemy.begin(); enemyIterator != theEnemy.end(); ++enemyIterator)//while the enemy is not dead check if collided, repeat for all enemies
		{
			if ((*enemyIterator)->SphereSphereCollision((*laserIterartor)->getPosition(), (*laserIterartor)->getMdlRadius()))//condition for the sphere collision detector
			{
				// if a collision set the bullet and spaceship to false
				(*enemyIterator)->setIsActive(false);
				(*laserIterartor)->setIsActive(false);
				// play the explosion sound.
				m_SoundMgr->getSnd("Explosion")->playAudio(AL_TRUE);
			}
		}
	}

	vector<cLaser*>::iterator laserIterartor = theTardisLasers.begin();//laser iterator set to active
	while (laserIterartor != theTardisLasers.end())//while laser  alive check
	{
		if ((*laserIterartor)->isActive() == false)//is laser iterator is not active? is so then
		{
			laserIterartor = theTardisLasers.erase(laserIterartor);//erase theTardisLasers laser iterator
		}
		else
		{
			++laserIterartor; //increase count of laser iterator
		}
	}

	vector<cEnemy*>::iterator enemyIterartor = theEnemy.begin();//enemy iterator set to active
	while (enemyIterartor != theEnemy.end())//while the enemy is alive
	{
		if ((*enemyIterartor)->isActive() == false)//check if enemy iterator is not active
		{
			enemyIterartor = theEnemy.erase(enemyIterartor);//if so delete the enemy iterator
		}
		else
		{
			++enemyIterartor;//increase the enemyIterator count
		}
	}

	// Find out what direction we should be thrusting, using rotation.
	glm::vec3 mdlVelocityAdd;
	mdlVelocityAdd.x = -(float)glm::sin(glm::radians(m_mdlRotation));  // Remember to adjust for radians
	mdlVelocityAdd.y = 0.0f;
	mdlVelocityAdd.z = -(float)glm::cos(glm::radians(m_mdlRotation));

	m_mdlRotation -= rotationAngle;//subtract rotation angle from private rotation variable

	mdlVelocityAdd *= translationZ;
	m_mdlDirection += mdlVelocityAdd;//add private velocityadd variable to private direction variable

	m_mdlPosition += m_mdlDirection * m_mdlSpeed *elapsedTime;//add the resultant calculations final answer to private position variabele
	m_mdlDirection *= 0.95f;

	rotationAngle = 0;//set rotation angle to 0
	translationZ = 0;//set translation to 0
}
void cPlayer::trigpulled(float elapsedTime){//function to fire a laser  on pulling a trigger on a gamepad needed to put the collision detection in again though
	//its inefficient but it should work
	glm::vec3 mdlLaserDirection;
	mdlLaserDirection.x = -(float)glm::sin(glm::radians(this->getRotation()));
	mdlLaserDirection.y = 0.0f;
	mdlLaserDirection.z = (float)glm::cos(glm::radians(this->getRotation()));
	mdlLaserDirection *= -1;

	// Add new bullet sprite to the vector array
	theTardisLasers.push_back(new cLaser);
	int numLasers = theTardisLasers.size() - 1;
	theTardisLasers[numLasers]->setDirection(mdlLaserDirection);
	theTardisLasers[numLasers]->setRotation(0.0f);
	theTardisLasers[numLasers]->setScale(glm::vec3(1, 1, 1));
	theTardisLasers[numLasers]->setSpeed(5.0f);
	theTardisLasers[numLasers]->setPosition(this->getPosition() + mdlLaserDirection);
	theTardisLasers[numLasers]->setIsActive(true);
	//theTardisLasers[numLasers]->setMdlDimensions(theLaser.getModelDimensions());
	theTardisLasers[numLasers]->update(elapsedTime);
	// play the firing sound
	energy = energy - 1;

	m_SoundMgr->getSnd("Blaster")->playAudio(AL_TRUE); //will play new blaster sound 

	for (vector<cLaser*>::iterator laserIterartor = theTardisLasers.begin(); laserIterartor != theTardisLasers.end(); ++laserIterartor)//as long as the laser is active proceed further
	{
		(*laserIterartor)->update(elapsedTime);//update laster with elapsed time
		for (vector<cEnemy*>::iterator enemyIterator = theEnemy.begin(); enemyIterator != theEnemy.end(); ++enemyIterator)//while the enemy is not dead check if collided, repeat for all enemies
		{
			if ((*enemyIterator)->SphereSphereCollision((*laserIterartor)->getPosition(), (*laserIterartor)->getMdlRadius()))//condition for the sphere collision detector
			{
				// if a collision set the bullet and spaceship to false
				(*enemyIterator)->setIsActive(false);
				(*laserIterartor)->setIsActive(false);
				// play the explosion sound.
				m_SoundMgr->getSnd("Explosion")->playAudio(AL_TRUE);
			}
		}
	}

	vector<cLaser*>::iterator laserIterartor = theTardisLasers.begin();//laser iterator set to active
	while (laserIterartor != theTardisLasers.end())//while laser  alive check
	{
		if ((*laserIterartor)->isActive() == false)//is laser iterator is not active? is so then
		{
			laserIterartor = theTardisLasers.erase(laserIterartor);//erase theTardisLasers laser iterator
		}
		else
		{
			++laserIterartor; //increase count of laser iterator
		}
	}

	vector<cEnemy*>::iterator enemyIterartor = theEnemy.begin();//enemy iterator set to active
	while (enemyIterartor != theEnemy.end())//while the enemy is alive
	{
		if ((*enemyIterartor)->isActive() == false)//check if enemy iterator is not active
		{
			enemyIterartor = theEnemy.erase(enemyIterartor);//if so delete the enemy iterator
		}
		else
		{
			++enemyIterartor;//increase the enemyIterator count
		}
	}

	// Find out what direction we should be thrusting, using rotation.
	glm::vec3 mdlVelocityAdd;
	mdlVelocityAdd.x = -(float)glm::sin(glm::radians(m_mdlRotation));  // Remember to adjust for radians
	mdlVelocityAdd.y = 0.0f;
	mdlVelocityAdd.z = -(float)glm::cos(glm::radians(m_mdlRotation));

	m_mdlRotation -= rotationAngle;//subtract rotation angle from private rotation variable

	mdlVelocityAdd *= translationZ;
	m_mdlDirection += mdlVelocityAdd;//add private velocityadd variable to private direction variable

	m_mdlPosition += m_mdlDirection * m_mdlSpeed *elapsedTime;//add the resultant calculations final answer to private position variabele
	m_mdlDirection *= 0.95f;

	rotationAngle = 0;//set rotation angle to 0
	translationZ = 0;//set translation to 0
}
cPlayer::~cPlayer()//deconstructor
{

}