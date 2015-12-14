#include "cLaser.h"

cLaser::cLaser() : cModel()//constructor
{

}

void cLaser::update(float elapsedTime)//update function passing in elapsed time float
{
	cModel::m_mdlPosition += cModel::m_mdlDirection * cModel::m_mdlSpeed * elapsedTime;//adjusting the coordinates and speed relative to the elapsed time
	if (cModel::m_mdlPosition.x > PLAYFIELDX ||
		cModel::m_mdlPosition.x < -PLAYFIELDX ||
		cModel::m_mdlPosition.z > PLAYFIELDZ ||
		cModel::m_mdlPosition.z < -PLAYFIELDZ)
		cModel::m_IsActive = false;//deactivates the laser model once it leaves the field of play specified in GameConstants.h

}

cLaser::~cLaser()//decostructor
{

}
