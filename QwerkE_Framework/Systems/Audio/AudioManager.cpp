#include "AudioManager.h"
#include "../../../QwerkE_Common/Utilities/PrintFunctions.h"

#include <stddef.h> // NULL

// OpenAL Reference: https://www.openal.org/documentation/OpenAL_Programmers_Guide.pdf
// wav loading: https://blog.csdn.net/u011417605/article/details/49662535
// const char* test_wav = "../../Shared_Generic/Resources/Sounds/Test.wav";

AudioManager::AudioManager()
{
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
		return;
	}
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