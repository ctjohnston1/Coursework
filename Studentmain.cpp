#define WIN32_LEAN_AND_MEAN
#define WIN32_EXTRA_LEAN

#define GLX_GLXEXT_LEGACY //Must be declared so that our local glxext.h is picked up, rather than the system one



//the includes for all the classes that are used in the program.
#include "GameConstants.h"
#include "windowOGL.h"
#include "cWNDManager.h"
#include "cColours.h"
#include "cShapes.h"
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
//include for the input/output stream, this is included to utilize the gamepad as it would have to be connected to the 
//device playing it
#include<iostream>

//main constructor for he program
int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR cmdLine,
                   int cmdShow)
{

    //Set our window settings
    const int windowWidth = 1024; //width of desired window
	const int windowHeight = 768; //height of desired window
    const int windowBPP = 16; 


	


    //This is our window
	//creates an instance of the class cWNDManager called pgmWNDMgr and calls its getInstance function.
	static cWNDManager* pgmWNDMgr = cWNDManager::getInstance();

	// This is the input manager
	//creates and instance of the cInputMgr class called theInputMgr and calls its getInstance function.
	static cInputMgr* theInputMgr = cInputMgr::getInstance();

	// This is the Font manager
	//creates an instance of the theFontMgr class called theFontMgr and calls its getInstance funciton.
	static cFontMgr* theFontMgr = cFontMgr::getInstance();

	// This is the sound manager
	//creates an instance of cSoundMgr called theSoundMgr and calles its getInstance function.
	static cSoundMgr* theSoundMgr = cSoundMgr::getInstance();
	
	//The example OpenGL code
	//instance of the of windowOGL named theOGLWind.
    windowOGL theOGLWnd;

    //Attach our example to our window
	//pgmWNDMgr pointer to attachOGLWnd by passing the instance of  it in essence attaches theOGLWnd object to pgmWNDMgr
	pgmWNDMgr->attachOGLWnd(&theOGLWnd);

	// Attach the keyboard manager
	//pgmWNDMgr pointer to attachInputMgr by passing the instance of theInputMgr, it in essence attaches theInputMgr object to pgmWNDMgr
	pgmWNDMgr->attachInputMgr(theInputMgr);


    //Attempt to create the window
	//if NOT pgmWDNMgr create a window using the specified parameters, these specific variables were declared earlier on in the code
	if (!pgmWNDMgr->createWND(windowWidth, windowHeight, windowBPP))
    {
        //If it fails
		//sends a message box with orange highlighted message
        MessageBox(NULL, "Unable to create the OpenGL Window", "An error occurred", MB_ICONERROR | MB_OK);
		//shuts down the window instead of repeatedly trying to create it
		pgmWNDMgr->destroyWND(); //Reset the display and exit
		//returns a value of one which 
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
	cTexture tardisTexture; //creates cTexture object called tardisTexture
	tardisTexture.createTexture("Models/tardis.png"); //specifies tardisTexture and calls create funciton with the filepath
	cTexture spaceShipTexture; //creates cTexture object claled spaceShipTexture
	spaceShipTexture.createTexture("Models/SpaceShip/sh3.jpg");//spaceShipTexture calls createTexture and passes in the specified file path
	cTexture laserTexture;//creates lasertexture object of class cTexture
	laserTexture.createTexture("Models/laser.tga");//lasertexture calls the create texture function and passes on the filepath specified
	cTexture starTexture;//creates instance of cTexture called star Texture
	starTexture.createTexture("Images/star.png");//star texture calls the create texture function and passes in the specified file path.
	cTexture moonTexture;//creates instance of cTexture called moonTexture
	moonTexture.createTexture("Models/Moon/Moon/MoonMap2_2500x1250.png");//moonTexture calls createTexture function  and passes in the filepath

	//assault ship texture
	cTexture assaultShipTexture; //creates texture called assaultShipTexture
	assaultShipTexture.createTexture("Models/UFO/UFO.tga"); //assaultShipTexture calls createTexture funciton and passes on the specified filepath


	//Gamepad instantiation
	Gamepad player1(1);
	// the starfield instantiation, and calls its texture and glm vec 3 value
	cStarfield theStarField(starTexture.getTexture(), glm::vec3(50.0f, 50.0f, 50.0f));

	// Create Materials for lights
	//creates instance of material class
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
	LPCSTR gameFonts[3] = { "Fonts/digital-7.ttf", "Fonts/space age.ttf", "Fonts/Stjldbl1.ttf" };//font filepaths added to the array
	//the font namees are specified and sent to the font manager with their corresponding array position and size
	theFontMgr->addFont("SevenSeg", gameFonts[0], 24);//add found sevenseg
	theFontMgr->addFont("Space", gameFonts[1], 24);
	theFontMgr->addFont("DrWho", gameFonts[2], 48);

	// load game sounds
	//  array is filled witht the filepaths of the sound files
	LPCSTR gameSounds[5] = { "Audio/DuelOfTheFates.wav", "Audio/Blaster.wav", "Audio/explosion2.wav", "Audio/win.wav", "Audio/no.wav" };
	//sound anager is sent the name specified and the corresponding member od the gamesound array
	theSoundMgr->add("Theme", gameSounds[0]);		//the theme was changed to duel of the fates
	theSoundMgr->add("Blaster", gameSounds[1]);		//shot's sound file was changes to the blaster sound effect
	theSoundMgr->add("Explosion", gameSounds[2]);	//explosion 2 will be kept as the sound effect suits the scene
	theSoundMgr->add("Win", gameSounds[3]);	//to play on defeating all the enemies
	theSoundMgr->add("No", gameSounds[4]); //to player on loosing all the energy

	// Create a camera
	cCamera theCamera; //the name of the camera
	theCamera.setTheCameraPos(glm::vec3(0.0f, 0.0f, 75.0f)); //sets position
	theCamera.setTheCameraLookAt(glm::vec3(0.0f, 0.0f, 0.0f)); //sets angle
	theCamera.setTheCameraUpVector(glm::vec3(0.0f, 1.0f, 0.0f)); // pointing upwards in world space
	theCamera.setTheCameraAspectRatio(windowWidth, windowHeight);//adjusts aspect depending on window size
	theCamera.setTheProjectionMatrix(45.0f, theCamera.getTheCameraAspectRatio(), 0.1f, 300.0f); //sets projection matrix with the last two numbers being the start view point and end view pointof the projection
	theCamera.update(); //update the camera

	//the second camera for the game
	cCamera birdsEye; //name of the camera
	birdsEye.setTheCameraPos(glm::vec3(50.0f, 0.0f, 75.0f)); //position of the camera
	birdsEye.setTheCameraLookAt(glm::vec3(0.0f, 0.0f, 0.0f));//sets angle
	birdsEye.setTheCameraUpVector(glm::vec3(0.0f, 1.0f, 0.0f)); //pointing upwards in the world space
	birdsEye.setTheCameraAspectRatio(windowWidth, windowHeight); //adjusts aspect depending on window size
	birdsEye.setTheProjectionMatrix(45.0f, birdsEye.getTheCameraAspectRatio(), 0.1f, 300.0f);//sets projection matrix
	birdsEye.update();//calls update function


	//loading sphere for deathstar in scene
	cSphere deathStar(2,20,20);//creates an instance of cSphere called deathstar and passes the values to give it its size
	cTexture deathTexture;//sets a texture called deathTexture
	deathTexture.createTexture("Images/deathstar.png"); //calls create function for deathTexture and passes in the filepath specified
	deathStar.initialise(deathTexture.getTexture(), glm::vec3(4,10,10),glm::vec3(0,0,0));//initialises deathstar


	//Clear key buffers
	theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);

	// Model
	cModelLoader tardisMdl;//calls instance of model loader called tardisMdl
	//tardisMdl calls load model function and passes in filepath and desired texture
	tardisMdl.loadModel("Models/UFO/UFO.obj", moonTexture); // Player

	//loads model called spaceShipMdl and assigns specified texture
	cModelLoader spaceShipMdl;
	spaceShipMdl.loadModel("Models/SpaceShip/Sample_Ship.obj", spaceShipTexture); // Enemy

	/*cModelLoader theMoon;
	theMoon.loadModel("Models/Moon/Moon/moon.obj", moonTexture);
	*/
	//loads model called the laser and assigns specified texture
	cModelLoader theLaser;
	theLaser.loadModel("Models/laser.obj", laserTexture);
	//for a loop of 6 create a new enemy ie this creates 6 enemies for the player to kill
	for (int loop = 0; loop < 6; loop++)
	{
		theEnemy.push_back(new cEnemy);
		theEnemy[loop]->randomise();//randomise where it is
		theEnemy[loop]->setMdlDimensions(spaceShipMdl.getModelDimensions()); //set models dimentions by calling them them
		theEnemy[loop]->setScale(glm::vec3(5, 5, 5));//scale it
	}

	//instance of cPlayer called thePlayer
	cPlayer thePlayer;
	thePlayer.initialise(glm::vec3(0, 0, 0), 0.0f, glm::vec3(1, 1, 1), glm::vec3(0, 0, 0), 5.0f, true); //initialise it and pass the parameters
	thePlayer.setMdlDimensions(tardisMdl.getModelDimensions());	//set dimentions by calling them
	thePlayer.attachInputMgr(theInputMgr);//attach theInputMgr to the player
	thePlayer.attachSoundMgr(theSoundMgr);//attach theSoundMgr to the player
	
	//variables to be used in the main loop
	float tCount = 0.0f;
	string outputMsg;
	string currentrotation;
	string amountOfEnergy;
	
//calling sountrack function and setting it to a variable 
	bool soundtrack = pgmWNDMgr->soundtrack();
	int sndvalidator = 0;

	//call the sound manager to get the specified sound and play the audio in a loop
		theSoundMgr->getSnd("Theme")->playAudio(AL_LOOPING);
	
		//math calc for vector made from cLaser called laserList, the same for index  it calls an iterator 
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
		//call the current value of camera
		bool cam = pgmWNDMgr->camera();
		if (cam == true){
				glLoadMatrixf((GLfloat*)&birdsEye.getTheViewMatrix()); //if true activate this camera to view out of
		}
		else{
			glLoadMatrixf((GLfloat*)&theCamera.getTheViewMatrix()); //if false this will be the camera that you see out of
		}
		
		///GAMEPAD CODE
		//these translations have been slowed considerably compared to the directional buttons on keyboard to decrease sensitivity
		player1.Update(); //call update of player1 gamepad 
		if (player1.Connected() == true) { //check if controller is connected
			OutputDebugString("Connected"); //if connected send this message to the debug lod
		}
		player1.GetState(); //get state of controller
		if (player1.LeftStick_Y() > 0.5f) { //if the left analogue stick  is tilted up 
			player1.Rumble(1.0f, 1.0f);//vibrate
			OutputDebugString("UP");//send message of log
			translationZ += 0.1f;//translate slowly
			player1.Rumble(0.0f, 0.0f);//turn off vibrate
		}
		if (player1.LeftStick_X() > 0.5f) {//if left analogue stick is tilted right
			player1.Rumble(1.0f, 1.0f);//vibrate
			OutputDebugString("RIGHT");//send message to log
			rotationAngle += 1.0f; //rotate slowly
			player1.Rumble(0.0f, 0.0f);//turn of vibrate
		}
		if (player1.LeftStick_Y() < -0.5f) {//if left analogue stick tilted down
			player1.Rumble(1.0f, 1.0f);//vibrate
			OutputDebugString("DOWN");//send message to log
			translationZ -= 0.1f;//translate slowly
			player1.Rumble(0.0f, 0.0f);//turn off vibrate
		}
		if (player1.LeftStick_X() < -0.5f) {//if left analogue stick tilted left
			player1.Rumble(1.0f, 1.0f);//vibrate
			OutputDebugString("LEFT");//send message to log
			rotationAngle -= 1.0f;//rotate slowly
			player1.Rumble(0.0f, 0.0f);//turn off vibrate
		}
		if (player1.LeftTrigger() > 0.5f) {//if left trigger pulled
			player1.Rumble(1.0f, 1.0f);//vibrate
			OutputDebugString("LEFT___FIRE___");//send message to log
			thePlayer.trigpulled(0.1f);//fire a laser by calling trigpulled method
			player1.Rumble(0.0f, 0.0f);//turn off vibrate
		}
		if (player1.RightTrigger() > 0.5f) {//if right trigger pulled 
			player1.Rumble(1.0f, 1.0f);//vibrate
			OutputDebugString("RIGHT___FIRE___");//send message to log
			thePlayer.trigpulled(0.1f);//fire laser by calling trigpulled method
			player1.Rumble(0.0f, 0.0f);//turn off vibrate
		}

		//deathStar.setRotAngle(deathStar.getRotAngle);
	//	deathStar.prepare(deathStar.getRotAngle);
		//sunMaterial.useMaterial();
		


		//	this is the soundswitch code
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
		//Render the star field
		theStarField.render(0.0f);
		//use the sunmaterial 
		sunMaterial.useMaterial();
		//activate the lights on the scene
		sunLight.lightOn();
		lfLight.lightOn();
		rfLight.lightOn();
		cbLight.lightOn();
		
		//render the death star
	deathStar.render(0.0f);
	//enemy iterator for their movement when they are still alive and loop for them all
		for (vector<cEnemy*>::iterator enemyIterator = theEnemy.begin(); enemyIterator != theEnemy.end(); ++enemyIterator)
		{
			if ((*enemyIterator)->isActive())
			{
				spaceShipMdl.renderMdl((*enemyIterator)->getPosition(), (*enemyIterator)->getRotation(), (*enemyIterator)->getScale());
				(*enemyIterator)->update(elapsedTime);
			}
		}

		//render the position of the player
		tardisMdl.renderMdl(thePlayer.getPosition(), thePlayer.getRotation(), thePlayer.getScale());
		//call the update function and pass in the elapsed time
		thePlayer.update(elapsedTime);
		//the iterator moving and rendering the lasers that have been fired looping for them all
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
		
		currentrotation = to_string(thePlayer.getRotation());//convert roation to string value
		amountOfEnergy = to_string(energy);//convert energy to string value
	
		glPushMatrix();//push the matrix
		theOGLWnd.setOrtho2D(windowWidth, windowHeight); //multiply current matrix with orthographic matric
		//place the fonts onto the screen by calling the font manager to get specified font ans printing the specified message in the commands
		//as well as seeing their position and their color which is currently all set to green for consistency of the overlay
		theFontMgr->getFont("DrWho")->printText("STAR WARS", FTPoint(10, 35, 0.0f), colour3f(0.0f,255.0f,0.0f));
		theFontMgr->getFont("Space")->printText(outputMsg.c_str(), FTPoint(850, 35, 0.0f), colour3f(255.0f, 255.0f, 0.0f)); // uses c_str to convert string to LPCSTR
		theFontMgr->getFont("Space")->printText("Your Current Rotation Angle: ", FTPoint(10, 80, 0.0f), colour3f(0.0f, 255.0f, 0.0f));
		theFontMgr->getFont("Space")->printText(currentrotation.c_str() , FTPoint(600, 80, 0.0f), colour3f(0.0f, 255.0f, 0.0f));
		theFontMgr->getFont("Space")->printText("Your Remaining Energy: ", FTPoint(10, 700, 0.0f), colour3f(0.0f, 255.0f, 0.0f));
		theFontMgr->getFont("Space")->printText(amountOfEnergy.c_str(), FTPoint(420, 700, 0.0f), colour3f(0.0f, 255.0f, 0.0f));
		glPopMatrix();
//the purpose of this if statement is to end the game if the energy levels of the player hit the specified number in this case 0
//or it ends the game on the condition
	
if (energy == 1){//set to one to trick bug in code so the sound will play on 0
	theSoundMgr->getSnd("No")->playAudio(AL_TRUE);
	theSoundMgr->getSnd("Theme")->stopAudio();				
		}
if (energy == -1){//game will end after a space press after reaching 0 
	theOGLWnd.shutdown(); //Free any resources
	pgmWNDMgr->destroyWND(); //Destroy the program window
	return 0; //Return success
}

if (theEnemy.size() == 1){//set to 1 to again trick the audio bug and play success message on 0 however it is stopped by the ending sequence which is next
	theSoundMgr->getSnd("Win")->playAudio(AL_TRUE);
	theSoundMgr->getSnd("Theme")->stopAudio();

}

if (theEnemy.size() == 0){ //shut down once 0 enemies
	
	theOGLWnd.shutdown(); //Free any resources
	pgmWNDMgr->destroyWND(); //Destroy the program window
	return 0; //Return success

}
pgmWNDMgr->swapBuffers();//swaps buffers

		tCount += elapsedTime;//add elapsed time to tCount

		//Clear key buffers
		theInputMgr->clearBuffers(theInputMgr->KEYS_DOWN_BUFFER | theInputMgr->KEYS_PRESSED_BUFFER);

	} //loop while finishing bracket

	theOGLWnd.shutdown(); //Free any resources
	pgmWNDMgr->destroyWND(); //Destroy the program window

    return 0; //Return success
}


