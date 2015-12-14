/*
==========================================================================
cSound.cpp
==========================================================================
*/
#pragma warning ( disable : 4996 )
#include "cSound.h"
using namespace std;

cSound::cSound()//constructor
{
	m_OALData = NULL;           //data for the buffer
	m_OALFrequency = 0;     //frequency
	m_OALBitRate = 0;		  // Bit Rate
	m_OALLength = 0;		  // Length
	m_OALBuffer = 0;         // Buffer

}

cSound::~cSound()//decondstructor
{

	cleanUp();
}

void cSound::loadWAVFile(LPCSTR filename)
{
	// Check for EAX 2.0 support
	m_OALbEAX = alIsExtensionPresent("EAX2.0");
	// Generate Buffers
	alGetError(); // clear error code

	//load the wave file
	alutLoadWAVFile((ALbyte *)filename, &m_OALFormat, (void **)&m_OALData, (ALsizei *)&m_OALBufferLen, &m_OALFrequency, &m_alLoop);

	//create a source
	alGenSources(1, &m_OALSource);

	//create  buffer
	alGenBuffers(1, &m_OALBuffer);

	//put the data into our sampleset buffer
	alBufferData(m_OALBuffer, m_OALFormat, m_OALData, m_OALBufferLen, m_OALFrequency);

	//assign the buffer to this source
	alSourcei(m_OALSource, AL_BUFFER, m_OALBuffer);

	//release the data
	alutUnloadWAV(m_OALFormat, m_OALData, m_OALBufferLen, m_OALFrequency);
}

void cSound::LoadWAVInfo(ifstream &filename, string &name, 	unsigned int &size)//loads the soundfile specified
{
	char chunk[4];
	filename.read((char *)&chunk, 4);
	filename.read((char *)&size, 4);

	name = string(chunk, 4);
}

void cSound::playAudio(ALboolean sndLoop)//plays the audio
{
	alSourcei(m_OALSource, sndLoop, AL_TRUE);

	//play
	alSourcePlay(m_OALSource);
}

void cSound::stopAudio()//stops the audio
{
	//to stop
	alSourceStop(m_OALSource);
}

void cSound::cleanUp()//clean up function stops audio and destroys the instances buffer and the information the instance ofcSound instance holds
{
	int state;
	alGetSourcei(m_OALSource, AL_SOURCE_STATE, &state);
	if (state == AL_PLAYING)
	{
		stopAudio();
	}

	alDeleteSources(1, &m_OALSource);

	//delete our buffer
	alDeleteBuffers(1, &m_OALBuffer);

	//Disable context
	alcMakeContextCurrent(NULL);

	//release the data
	delete m_OALData;
}
