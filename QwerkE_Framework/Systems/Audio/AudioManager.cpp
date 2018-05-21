#include "AudioManager.h"
#include "../../../QwerkE_Common/Utilities/PrintFunctions.h"
#include "../../../QwerkE_Common/Utilities/FileIO/FileLoader/LoadWavFile.h"
#include "../../QwerkE_Directory_Defines.h"
#include "../../../QwerkE_Common/Utilities/StringHelpers.h"
#include "../ServiceLocator.h"
#include "../ResourceManager/ResourceManager.h"

// OpenAL Reference: https://www.openal.org/documentation/OpenAL_Programmers_Guide.pdf
// wav loading: https://blog.csdn.net/u011417605/article/details/49662535
// https://ffainelli.github.io/openal-example/
// https://stackoverflow.com/questions/13660777/c-reading-the-data-part-of-a-wav-file/13661263

void OpenALError(ALenum error)
{
	switch (error)
	{
	// case AL_INVALID_DEVICE:
	// case AL_INVALID_CONTEXT:
	case AL_INVALID_ENUM:
		OutputPrint("AL_INVALID_ENUM");
		break;
	case AL_INVALID_VALUE:
		OutputPrint("AL_INVALID_VALUE");
		break;
	case AL_OUT_OF_MEMORY:
		OutputPrint("AL_OUT_OF_MEMORY");
		break;
	default:
		OutputPrint("Unknown error!");
		break;
	}
}

// TODO: Source this or rewrite
static void list_audio_devices(const ALCchar *devices)
{
	const ALCchar *device = devices, *next = devices + 1;
	size_t len = 0;

	fprintf(stdout, "Devices list:\n");
	fprintf(stdout, "----------\n");
	while (device && *device != '\0' && next && *next != '\0') {
		fprintf(stdout, "%s\n", device);
		len = strlen(device);
		device += (len + 1);
		next += (len + 2);
	}
	fprintf(stdout, "----------\n");
}

AudioManager::AudioManager()
{
	// Initialization

	ALuint error;
	// TODO: Setup device properly
	list_audio_devices(alcGetString(NULL, ALC_DEVICE_SPECIFIER));
	Device = alcOpenDevice("OpenAL Soft"); // select the "preferred device"

	assert(Device); // ALDevice error

	Context = alcCreateContext(Device, NULL);
	alcMakeContextCurrent(Context);

	// Check for EAX 2.0 support
	g_bEAX = alIsExtensionPresent("EAX2.0"); // Why?
	const ALCchar* result = alcGetString(Device, AL_EXTENSIONS); // check for extensions

	// if(result != nullptr) ConsolePrint("\nOpenAL extensions available!!!\n");

	error = alGetError();
	if (error != AL_NO_ERROR)
		OpenALError(error);

	// TODO: Move this code to a better spot
	ALuint handle = 0;
	DWORD size;
	unsigned short channels;
	ALsizei frequency;
	unsigned char* data = QwerkE_wav_loadSound(SoundFolderPath("bounce.wav"), size, channels, frequency);
	// TODO: read format type and handle loading various sound formats
	if (channels == 1)
		alBufferData(handle, AL_FORMAT_MONO16, data, size, frequency);
	else if (channels == 2)
		alBufferData(handle, AL_FORMAT_STEREO16, data, size, frequency);
	else
	{
		// invalid number of channels
	}

	((ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager))->AddSound(
		"bounce.wav", handle);

	error = alGetError();
	if (error != AL_NO_ERROR)
		OpenALError(error);

	if (error != AL_NO_ERROR || handle != 1) // TODO: Better error checking
		ConsolePrint("\nOpenAL error buffering sound data!\n");

	SetListenerOrientation(vec3(0,0,0), vec3(0,0,0));

	error = alGetError();
	if (error != AL_NO_ERROR)
		OpenALError(error);

	if (error == AL_NO_ERROR || handle == 1) // TODO: Better error checking
		ConsolePrint("\nOpenAL loaded successfully\n\n");
}

AudioManager::~AudioManager()
{
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
	if (!((ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager))->SoundExists(name))
	alSourcePlay(((ResourceManager*)QwerkE::ServiceLocator::GetService(eEngineServices::Resource_Manager))->GetSound(name));
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
