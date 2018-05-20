#include "AudioManager.h"
#include "AudioSource.h"
#include "../../../QwerkE_Common/Utilities/PrintFunctions.h"
#include "../../../QwerkE_Common/Utilities/FileIO/FileLoader/LoadWavFile.h"
#include "../../QwerkE_Directory_Defines.h"
#include "../../../QwerkE_Common/Utilities/StringHelpers.h"

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

	// create sound buffers
	for (int i = 0; i < NUM_BUFFERS; i++)
	{
		ALuint temp;
		alGenBuffers(1, &temp);
		m_SoundBuffers.push_back(temp);
	}

	// TODO: Move this code to a better spot
	DWORD size;
	unsigned short channels;
	ALsizei frequency;
	unsigned char* data = QwerkE_wav_loadSound(SoundFolderPath("bounce.wav"), size, channels, frequency);
	// TODO: read format type and handle loading various sound formats
	if (channels == 1)
		alBufferData(m_SoundBuffers.at(0), AL_FORMAT_MONO16, data, size, frequency);
	else if (channels == 2)
		alBufferData(m_SoundBuffers.at(0), AL_FORMAT_STEREO16, data, size, frequency);
	else
	{
		assert(false); // invalid channels
	}

	error = alGetError();
	if (error != AL_NO_ERROR)
		OpenALError(error);

	if (error != AL_NO_ERROR || m_SoundBuffers[0] != 1) // TODO: Better error checking
		ConsolePrint("\nOpenAL error buffering sound data!\n");

	SetListenerOrientation(vec3(0,0,0), vec3(0,0,0));

	m_Source = new AudioSource();
	m_Source->SetOrientation(vec3(0,0,0), vec3(0,0,0), vec3(0,0,0));
	// m_Source->Play(m_SoundBuffers.at(0));

	error = alGetError();
	if (error != AL_NO_ERROR)
		OpenALError(error);

	if (error == AL_NO_ERROR || m_SoundBuffers[0] == 1) // TODO: Better error checking
		ConsolePrint("\nOpenAL loaded successfully\n\n");

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
	m_Source->Play(m_SoundBuffers.at(0));
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