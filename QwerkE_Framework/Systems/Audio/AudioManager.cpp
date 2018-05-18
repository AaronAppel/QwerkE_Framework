#include "AudioManager.h"
#include "../../../QwerkE_Common/Utilities/PrintFunctions.h"
#include "../../../QwerkE_Common/Utilities/FileIO/LoadWavFile.h"

#include <stddef.h> // NULL

// OpenAL Reference: https://www.openal.org/documentation/OpenAL_Programmers_Guide.pdf
// wav loading: https://blog.csdn.net/u011417605/article/details/49662535
// https://ffainelli.github.io/openal-example/
// https://blogs.fsfe.org/jzarl/2013/10/15/openal-replacing-alutloadwavfile/
// const char* test_wav = "../../Shared_Common/Resources/Sounds/Test.wav";

AudioManager::AudioManager()
{
	// init openal?

	// Initialization
	Device = alcOpenDevice(NULL); // select the "preferred device"

	if (Device) {
		Context = alcCreateContext(Device, NULL);
		alcMakeContextCurrent(Context);
	}
	// Check for EAX 2.0 support
	g_bEAX = alIsExtensionPresent("EAX2.0");
	// Generate Buffers
	alGetError(); // clear error code
	alGenBuffers(NUM_BUFFERS, g_Buffers);

	ALenum error;
	if ((error = alGetError()) != AL_NO_ERROR)
	{
		// DisplayALError("alGenBuffers :", error);
		ConsolePrint("\nError loading OpenAL!\n");
	}

	Context = alcCreateContext(Device, NULL);
	if (!alcMakeContextCurrent(Context))
	{
		// failed
	}
	// alGetError()

	//// setup default listener object
	// TODO: Create an AudioListener() object or component/routine pair
	// that will remember and manipulate listener data.
	ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };

	alListener3f(AL_POSITION, 0, 0, 1.0f);
	// check for errors
	alListener3f(AL_VELOCITY, 0, 0, 0);
	// check for errors
	alListenerfv(AL_ORIENTATION, listenerOri);
	// check for errors

	//// create audio source object (sound player)
	ALuint source;

	alGenSources((ALuint)1, &source);
	// check for errors

	alSourcef(source, AL_PITCH, 1);
	// check for errors
	alSourcef(source, AL_GAIN, 1);
	// check for errors
	alSource3f(source, AL_POSITION, 0, 0, 0);
	// check for errors
	alSource3f(source, AL_VELOCITY, 0, 0, 0);
	// check for errors
	alSourcei(source, AL_LOOPING, AL_FALSE);
	// check for errors

	//// generate a stream buffer object
	ALuint buffer;

	alGenBuffers((ALuint)1, &buffer);
	// check for errors
	ALsizei size, freq;
	ALenum format;
	ALvoid* data;
	ALboolean loop = AL_FALSE;

	const char* filename = "test.wav";
	// https://mackron.github.io/dr_wav
	// http://wascal.net/music/?p=369
	// https://stackoverflow.com/questions/16075233/reading-and-processing-wav-file-data-in-c-c

	// alSourcePlay(source); // play

	//alutLoadWAVFile((ALbyte*)filename, &format, &data, &size, &freq, &loop);

	//// load an audio stream to a buffer
	// LoadWavFile("../../../QwerkE_Common/Resources/Sounds/Test.wav", buffer);
	// check for errors

	/*
	// Load test.wav
	loadWAVFile(test_wav, &format, &data, &size, &freq, &loop);
	if ((error = alGetError()) != AL_NO_ERROR)
	{
	// DisplayALError("alutLoadWAVFile test.wav : ", error);
	alDeleteBuffers(NUM_BUFFERS, g_Buffers);
	return;
	}
	// Copy test.wav data into AL Buffer 0
	alBufferData(g_Buffers[0], format, data, size, freq);
	if ((error = alGetError()) != AL_NO_ERROR)
	{
	// DisplayALError("alBufferData buffer 0 : ", error);
	alDeleteBuffers(NUM_BUFFERS, g_Buffers);
	return;
	}
	*/
}

AudioManager::~AudioManager()
{
	/*
	// Unload test.wav
	unloadWAV(format, data, size, freq);
	if ((error = alGetError()) != AL_NO_ERROR)
	{
	// DisplayALError("alutUnloadWAV : ", error);
	alDeleteBuffers(NUM_BUFFERS, g_Buffers);
	return;
	}
	// Exit
	Context = alcGetCurrentContext();
	Device = alcGetContextsDevice(Context);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(Context);
	alcCloseDevice(Device);
	*/
}

void AudioManager::PlaySound()
{
	ConsolePrint("\nSound requested!");
}

/*
// Generate Sources
alGenSources(1,source);
if ((error = alGetError()) != AL_NO_ERROR)
{
DisplayALError("alGenSources 1 : ", error);
return;
}
// Attach buffer 0 to source
- 10 -
alSourcei(source[0], AL_BUFFER, g_Buffers[0]);
if ((error = alGetError()) != AL_NO_ERROR)
{
DisplayALError("alSourcei AL_BUFFER 0 : ", error);
}
*/