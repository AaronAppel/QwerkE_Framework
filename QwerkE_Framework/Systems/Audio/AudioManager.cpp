#include "AudioManager.h"
#include "../../../QwerkE_Common/Utilities/PrintFunctions.h"
#include "../ServiceLocator.h"
#include "../FileSystem/FileSystem.h"
#include "../../QwerkE_Directory_Defines.h"
#include "../../../QwerkE_Common/Utilities/StringHelpers.h"
#include "../ServiceLocator.h"
#include "../ResourceManager/ResourceManager.h"
#include "OpenAL_Helpers.h"
#include "AudioSource.h"

// OpenAL Reference: https://www.openal.org/documentation/OpenAL_Programmers_Guide.pdf

AudioManager::AudioManager()
{
	ALuint error;

	std::string deviceName = list_audio_devices(alcGetString(NULL, ALC_DEVICE_SPECIFIER));
	Device = alcOpenDevice(deviceName.c_str()); // select the "preferred device"

	assert(Device); // ALDevice error

	Context = alcCreateContext(Device, NULL);
	alcMakeContextCurrent(Context);

	// Check for EAX 2.0 support
	// g_bEAX = alIsExtensionPresent("EAX2.0"); // Why?
	// const ALCchar* result = alcGetString(Device, AL_EXTENSIONS); // check for extensions
	// if(result != nullptr) ConsolePrint("\nOpenAL extensions available!!!\n");

	m_Source = new AudioSource();
	m_Source->SetOrientation(vec3(0, 0, 0), vec3(0, 0, 0), vec3(0, 0, 0));

	SetListenerOrientation(vec3(0,0,0), vec3(0,0,0));

	ConsolePrint("\nOpenAL loaded successfully\n\n");
}

AudioManager::~AudioManager()
{
	delete m_Source;
	// TODO: cleanup openal
	/*
	alDeleteBuffers(NUM_BUFFERS, g_Buffers);
	Context = alcGetCurrentContext();
	Device = alcGetContextsDevice(Context);
	alcMakeContextCurrent(NULL);
	alcDestroyContext(Context);
	alcCloseDevice(Device);
	*/
}

void AudioManager::PlaySound(const char* name)
{
	m_Source->Play(((ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager))->GetSound(name));
}


void AudioManager::SetListenerOrientation(vec3 position, vec3 velocity)
{
	// TODO: Create an AudioListener() object or component/routine pair
	// that will remember and manipulate listener data.
	alListenerf(AL_GAIN, 0.5f);
	alListener3f(AL_POSITION, position.x, position.y, position.z);
	alListener3f(AL_VELOCITY, velocity.x, velocity.y, velocity.z);
	ALfloat listenerOri[] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
	alListenerfv(AL_ORIENTATION, listenerOri);
}
