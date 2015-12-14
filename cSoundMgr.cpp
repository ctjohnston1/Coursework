/*
==================================================================================
cSoundMgr.cpp
==================================================================================
*/

#include "cSoundMgr.h"

cSoundMgr* cSoundMgr::pInstance = NULL;

/*
=================================================================================
Constructor
=================================================================================
*/
cSoundMgr::cSoundMgr()
{
	createContext();
}

/*
=================================================================================
Singleton Design Pattern
=================================================================================
*/
cSoundMgr* cSoundMgr::getInstance()
{
	if (pInstance == NULL)
	{
		pInstance = new cSoundMgr();
	}
	return cSoundMgr::pInstance;
}

void cSoundMgr::createContext()//create context function
{
	m_OALDevice = alcOpenDevice(NULL);
	if (m_OALDevice)
	{
		//Create a context
		m_OALContext = alcCreateContext(m_OALDevice, NULL);

		//Set active context
		alcMakeContextCurrent(m_OALContext);
	}
}

void cSoundMgr::add(LPCSTR sndName, LPCSTR fileName)//add sound with the sound name and its filepath
{
	if (!getSnd(sndName))//if the current sound name doesnt equal the one being passed in the create a new sound (allows for more than one sound to be managed)
	{
		cSound * newSnd = new cSound();
		newSnd->loadWAVFile(fileName);
		gameSnds.insert(make_pair(sndName, newSnd));
	}
}

cSound* cSoundMgr::getSnd(LPCSTR sndName)//return sound value
{
	map<LPCSTR, cSound*>::iterator snd = gameSnds.find(sndName);//looks for sound name
	if (snd != gameSnds.end())
	{
		return snd->second;
	}
	else
	{
		return NULL;
	}
}

void cSoundMgr::deleteSnd()
{
	for (map<LPCSTR, cSound*>::iterator snd = gameSnds.begin(); snd != gameSnds.end(); ++snd)
	{
		delete snd->second;
	}
}


cSoundMgr::~cSoundMgr()//deconstructor, deletes the indormation the variables hold and closes devices and destroys buffers of the particular
						//instance that calls it
{
	m_OALContext = alcGetCurrentContext();

	//Get device for active context
	m_OALDevice = alcGetContextsDevice(m_OALContext);

	//Release context(s)
	alcDestroyContext(m_OALContext);

	//Close device
	alcCloseDevice(m_OALDevice);

}
