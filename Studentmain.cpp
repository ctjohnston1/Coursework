#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#define GLX_GLXEXT_LEGACY //Must be declared so that our local glxext.h is picked up, rather than the system one

//a check to make sure git hub works

//#include <windows.h>
#include "GameConstants.h"
#include "windowOGL.h"
#include "cWNDManager.h"
#include "cColours.h"
#include "cShapes.h"
#include "cPyramid.h"
#include "cCube.h"
#include "cSphere.h"
#include "cMaterial.h"
#include "cLight.h"
#include "cStarfield.h"
#include "cFontMgr.h"
#include "cCamera.h"
#include "cInputMgr.h"
#include "cSoundMgr.h"
#include "cModelLoader.h"
#include "cModel.h"
#include "cPlayer.h"
#include "cEnemy.h"
#include "cLaser.h"
#include "tardisWarsGame.h"

#include "Gamepad.h"
#include<iostream>

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR cmdLine,
                   int cmdShow)
{

    //Set our window settings
    const int windowWidth = 1024;
    const int windowHeight = 768;
    const int windowBPP = 16;


	


    //This is our window
	static cWNDManager* pgmWNDMgr = cWNDManager::getInstance();

	// This is the input manager
	static cInputMgr* theInputMgr = cInputMgr::getInstance();

	// This is the Font manager
	static cFontMgr* theFontMgr = cFontMgr::getInstance();

	// This is the sound manager
	static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();
	
	//The example OpenGL code
    windowOGL theOGLWnd;

    //Attach our example to our window
	pgmWNDMgr->attachOGLWnd(&theOGLWnd);

	// Attach the keyboard manager
	pgmWNDMgr->attachInputMgr(theInputMgr);


    //Attempt to create the window
	if (!pgmWNDMgr->createWND(windowWidth, windowHeight, windowBPP))
    {
        //If it fails

        MessageBox(NULL, "Unable to create the OpenGL Window", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
        return 1;
    }

	if (!theOGLWnd.initOGL(windowWidth, windowHeight)) //Initialize our example
    {
        MessageBox(NULL, "Could not initialize the application", "An error occurred", MB_ICONERROR | MB_OK);
		pgmWNDMgr->destroyWND(); //Reset the display and exit
        return 1;
    }
	//string specialChar;
	
	//game pad code


	// Create Texture map
	cTexture tardisTexture;
	tardisTexture.createTexture("Models/tardis.png");
	cTexture spaceShipTexture;
	spaceShipTexture.createTexture("Models/SpaceShip/sh3.jpg");
	cTexture laserTexture;
	laserTexture.createTexture("Models/laser.tga");
	cTexture starTexture;
	starTexture.createTexture("Images/star.png");
	cTexture moonTexture;
	moonTexture.createTexture("Models/Moon/Moon/MoonMap2_2500x1250.png");

	//assault ship texture
	cTexture assaultShipTexture;
	assaultShipTexture.createTexture("Models/UFO/UFO.tga");


	//Gamepad instantiation
	Gamepad player1(1);
	// the starfield
	cStarfield theStarField(starTexture.getTexture(), glm::vec3(50.0f, 50.0f, 50.0f));

	// Create Materials for lights
	cMaterial sunMaterial(lightColour4(0.0f, 0.0f, 0.0f, 1.0f), lightColour4(1.0f, 1.0f, 1.0f, 1.0f), lightColour4(1.0f, 1.0f, 1.0f, 1.0f), lightColour4(0, 0, 0, 1.0f), 5.0f);

	// Create Light
	cLight sunLight(GL_LIGHT0, lightColour4(0, 0, 0, 1), lightColour4(10, 10, 10, 1), lightColour4(10, 10, 10, 1), glm::vec4(0, 0, 20, 1),
		glm::vec3(0.0, 0.0, 1.0), 0.0f, 180.0f, 1.0f, 0.0f, 0.0f);
	cLight lfLight(GL_LIGHT1, lightColour4(0, 0, 0, 1), lightColour4(1, 1, 1, 1), lightColour4(1, 1, 1, 1), glm::vec4(30, 0, 100, 1),
		glm::vec3(0.0, 0.0, 1.0), 0.0f, 180.0f, 1.0f, 0.0f, 0.0f);
	cLight rfLight(GL_LIGHT2, lightColour4(0, 0, 0, 1), lightColour4(1, 1, 1, 1), lightColour4(1, 1, 1, 1), glm::vec4(-30, 0, 100, 1),
		glm::vec3(0.0, 0.0, 1.0), 0.0f, 180.0f, 1.0f, 0.0f, 0.0f);
	cLight cbLight(GL_LIGHT3, lightColour4(0, 0, 0, 1), lightColour4(1, 1, 1, 1), lightColour4(1, 1, 1, 1), glm::vec4(0, 0, -100, 1),
		glm::vec3(0.0, 0.0, 1.0), 0.0f, 180.0f, 1.0f, 0.0f, 0.0f);


	
	//light for the Deathstar  :: note that the glm vec 4 value was changed
	cLight deathLight(GL_LIGHT3, lightColour4(0, 0, 0, 1), lightColour4(1, 1, 1, 1), lightColour4(1, 1, 1, 1), glm::vec4(0, 0, 0, 1),
		glm::vec3(0.0, 0.0, 1.0), 0.0f, 180.0f, 1.0f, 0.0f, 0.0f);

	//Define Ambient light for scene
	GLfloat g_Ambient[] = { 10.2, 10.2, 10.2, 1.0 };
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, g_Ambient);

	// load game fonts
	// Load Fonts
	LPCSTR gameFonts[3] = { "Fonts/digital-7.ttf", "Fonts/space age.ttf", "Fonts/Stjldbl1.ttf" };

	theFontMgr->addFont("SevenSeg", gameFonts[0], 24);
	theFontMgr->addFont("Space", gameFonts[1], 24);
	theFontMgr->addFont("DrWho", gameFonts[2], 48);

	// load game sounds
	// Load Sound
	LPCSTR gameSounds[5] = { "Audio/DuelOfTheFates.wav", "Audio/Blaster.wav", "Audio/explosion2.wav", "Audio/win.wav", "Audio/no.wav" };

	theSoundMgr->add("Theme", gameSounds[0]);		//the theme was changed to duel of the fates
	theSoundMgr->add("Blaster", gameSounds[1]);		//shot's sound file was changes to the blaster sound effect
	theSoundMgr->add("Explosion", gameSounds[2]);	//explosion 2 will be kept as the sound effect suits the scene
	theSoundMgr->add("Win", gameSounds[3]);	
	theSoundMgr->add("No", gameSounds[4]);

	// Create a camera
	cCamera theCamera;
	theCamera.setTheCameraPos(glm::vec3(0.0f, 0.0f, 75.0f));
	theCamera.setTheCameraLookAt(glm::vec3(0.0f, 0.0f, 0.0f));
	theCamera.setTheCameraUpVector(glm::vec3(0.0f, 1.0f, 0.0f)); // pointing upwards in world space
	theCamera.setTheCameraAspectRatio(windowWidth, windowHeight);
	theCamera.setTheProjectionMatrix(45.0f, theCamera.getTheCameraAspectRatio(), 0.1f, 300.0f);
	theCamera.update();

	//the second camera for the game
	cCamera birdsEye;
	birdsEye.setTheCameraPos(glm::vec3(50.0f, 0.0f, 75.0f));
	birdsEye.setTheCameraLookAt(glm::vec3(0.0f, 0.0f, 0.0f));
	birdsEye.setTheCameraUpVector(glm::vec3(0.0f, 1.0f, 0.0f)); 
	birdsEye.setTheCameraAspectRatio(windowWidth, windowHeight);
	birdsEye.setTheProjectionMatrix(45.0f, birdsEye.getTheCameraAspectRatio(), 0.1f, 300.0f);
	birdsEye.update();


	//loading sphere for deathstar in scene
	cSphere deathStar(2,20,20);
	cTexture deathTexture;
	deathTexture.createTexture("Images/deathstar.png");
	deathStar.initialise(deathTexture.getTexture(), glm::vec3(4,10,10),glm::vec3(0,0,0));


	//Clear key buffers
	theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);

	// Model
	cModelLoader tardisMdl;
	tardisMdl.loadModel("Models/UFO/UFO.obj", moonTexture); // Player

	cModelLoader spaceShipMdl;
	spaceShipMdl.loadModel("Models/SpaceShip/Sample_Ship.obj", spaceShipTexture); // Enemy

	/*cModelLoader theMoon;
	theMoon.loadModel("Models/Moon/Moon/moon.obj", moonTexture);
	*/
	cModelLoader theLaser;
	theLaser.loadModel("Models/laser.obj", laserTexture);
	
	for (int loop = 0; loop < 6; loop++)
	{
		theEnemy.push_back(new cEnemy);
		theEnemy[loop]->randomise();
		theEnemy[loop]->setMdlDimensions(spaceShipMdl.getModelDimensions());
		theEnemy[loop]->setScale(glm::vec3(5, 5, 5));
	}


	cPlayer thePlayer;
	thePlayer.initialise(glm::vec3(0, 0, 0), 0.0f, glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), 5.0f, true);
	thePlayer.setMdlDimensions(tardisMdl.getModelDimensions());	
	thePlayer.attachInputMgr(theInputMgr);
	thePlayer.attachSoundMgr(theSoundMgr);
	

	float tCount = 0.0f;

	string outputMsg;
	string currentrotation;
	string amountOfEnergy;
	
	bool soundtrack = pgmWNDMgr->soundtrack();
	int sndvalidator = 0;

	
		theSoundMgr->getSnd("Theme")->playAudio(AL_LOOPING);
	

	std::vector<cLaser*> laserList;
	std::vector<cLaser*>::iterator index;
	
   //This is the mainloop, we render frames until isRunning returns false
	while (pgmWNDMgr->isWNDRunning())
    {
		pgmWNDMgr->processWNDEvents(); //Process any window events
		

        //We get the time that passed since the last frame
		float elapsedTime = pgmWNDMgr->getElapsedSeconds();
		
		// Lab code goes here
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		theOGLWnd.initOGL(windowWidth,windowHeight);
		
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		bool cam = pgmWNDMgr->camera();
		if (cam == true){
				glLoadMatrixf((GLfloat*)&birdsEye.getTheViewMatrix());
		}
		else{
			glLoadMatrixf((GLfloat*)&theCamera.getTheViewMatrix());
		}
		

		player1.Update();
		if (player1.Connected() == true) {
			OutputDebugString("Connected");
		}
		player1.GetState();
		if (player1.LeftStick_Y() > 0.5f) {
			player1.Rumble(1.0f, 1.0f);
			OutputDebugString("UP");
			translationZ += 0.1f;
			player1.Rumble(0.0f, 0.0f);
		}
		if (player1.LeftStick_X() > 0.5f) {
			player1.Rumble(1.0f, 1.0f);
			OutputDebugString("RIGHT");
			rotationAngle += 1.0f;
			player1.Rumble(0.0f, 0.0f);
		}
		if (player1.LeftStick_Y() < 0.5f) {
			player1.Rumble(1.0f, 1.0f);
			OutputDebugString("DOWN");
			translationZ -= 0.1f;
			player1.Rumble(0.0f, 0.0f);
		}
		if (player1.LeftStick_X() < 0.5f) {
			player1.Rumble(1.0f, 1.0f);
			OutputDebugString("LEFT");
			rotationAngle -= 1.0f;
			player1.Rumble(0.0f, 0.0f);
		}
		if (player1.LeftTrigger() > 0.5f) {
			player1.Rumble(1.0f, 1.0f);
			OutputDebugString("LEFT___FIRE___");
			thePlayer.trigpulled(0.1f);
			player1.Rumble(0.0f, 0.0f);
		}
		if (player1.RightTrigger() > 0.5f) {
			player1.Rumble(1.0f, 1.0f);
			OutputDebugString("RIGHT___FIRE___");
			thePlayer.trigpulled(0.1f);
			player1.Rumble(0.0f, 0.0f);
		}

		//deathStar.setRotAngle(deathStar.getRotAngle);
	//	deathStar.prepare(deathStar.getRotAngle);
		//sunMaterial.useMaterial();
		
		bool soundtrack = pgmWNDMgr->soundtrack();
		if (soundtrack == true){
			theSoundMgr->getSnd("Theme")->stopAudio();
			if (sndvalidator > 0){
				theSoundMgr->getSnd("Theme")->playAudio(AL_LOOPING);
				//this is the code that will activate on pulling the left trigger on the gamepad
				//thePlayer.trigpulled(0.0f);
			}
			sndvalidator += 1;

		}
		theStarField.render(0.0f);
		sunMaterial.useMaterial();
		sunLight.lightOn();
		lfLight.lightOn();
		rfLight.lightOn();
		cbLight.lightOn();
		

	deathStar.render(0.0f);
	
		for (vector<cEnemy*>::iterator enemyIterator = theEnemy.begin(); enemyIterator != theEnemy.end(); ++enemyIterator)
		{
			if ((*enemyIterator)->isActive())
			{
				spaceShipMdl.renderMdl((*enemyIterator)->getPosition(), (*enemyIterator)->getRotation(), (*enemyIterator)->getScale());
				(*enemyIterator)->update(elapsedTime);
			}
		}

		tardisMdl.renderMdl(thePlayer.getPosition(), thePlayer.getRotation(), thePlayer.getScale());
		thePlayer.update(elapsedTime);
		
		for (vector<cLaser*>::iterator laserIterartor = theTardisLasers.begin(); laserIterartor != theTardisLasers.end(); ++laserIterartor)
		{
			if ((*laserIterartor)->isActive())
			{
				theLaser.renderMdl((*laserIterartor)->getPosition(), (*laserIterartor)->getRotation(), (*laserIterartor)->getScale());
				(*laserIterartor)->update(elapsedTime);
			}
		}
		//git hub error appeared a change is needed to check it
		outputMsg = to_string(theEnemy.size()); // convert float to string
		
		currentrotation = to_string(thePlayer.getRotation());
		amountOfEnergy = to_string(energy);
	
		glPushMatrix();
		theOGLWnd.setOrtho2D(windowWidth, windowHeight);

		theFontMgr->getFont("DrWho")->printText("STAR WARS", FTPoint(10, 35, 0.0f), colour3f(0.0f,255.0f,0.0f));
		theFontMgr->getFont("Space")->printText(outputMsg.c_str(), FTPoint(850, 35, 0.0f), colour3f(255.0f, 255.0f, 0.0f)); // uses c_str to convert string to LPCSTR
		theFontMgr->getFont("Space")->printText("Your Current Rotation Angle: ", FTPoint(10, 80, 0.0f), colour3f(0.0f, 255.0f, 0.0f));
		theFontMgr->getFont("Space")->printText(currentrotation.c_str() , FTPoint(600, 80, 0.0f), colour3f(0.0f, 255.0f, 0.0f));
		theFontMgr->getFont("Space")->printText("Your Remaining Energy: ", FTPoint(10, 700, 0.0f), colour3f(0.0f, 255.0f, 0.0f));
		theFontMgr->getFont("Space")->printText(amountOfEnergy.c_str(), FTPoint(420, 700, 0.0f), colour3f(0.0f, 255.0f, 0.0f));
		glPopMatrix();//850
//the purpose of this if statement is to end the game if the energy levels of the player hit the specified number in this case 0
//or it ends the game on the condition
	
if (energy == 1){
	theSoundMgr->getSnd("No")->playAudio(AL_TRUE);
	theSoundMgr->getSnd("Theme")->stopAudio();				
		}
if (energy == -1){
	theOGLWnd.shutdown(); //Free any resources
	pgmWNDMgr->destroyWND(); //Destroy the program window
	return 0; //Return success
}

if (theEnemy.size() == 1){
	theSoundMgr->getSnd("Win")->playAudio(AL_TRUE);
	theSoundMgr->getSnd("Theme")->stopAudio();

}

if (theEnemy.size() == 0){
	
	theOGLWnd.shutdown(); //Free any resources
	pgmWNDMgr->destroyWND(); //Destroy the program window
	return 0; //Return success

}
pgmWNDMgr->swapBuffers();

		tCount += elapsedTime;

		//Clear key buffers
		theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);

	}

	theOGLWnd.shutdown(); //Free any resources
	pgmWNDMgr->destroyWND(); //Destroy the program window

    return 0; //Return success
}


