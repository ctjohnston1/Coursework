/*
==================================================================================
GameConstants.cpp
==================================================================================
*/

#include "GameConstants.h"
//the variabel that may be accessed and changed at any point in the main cpp without declaration
int drawMode = 0;
float rotationAngle = 0; //players rotation
float translationZ = 0; //players location
bool fire = false; //is the ship firing its laser
int energy = 200; //this is the value of energy ie the amount of laser bullets that you can fire
					//also note that energy value was modified to 500 in the video so that the chances of success were high enough
					//to demonstrate the game ending on victory.

