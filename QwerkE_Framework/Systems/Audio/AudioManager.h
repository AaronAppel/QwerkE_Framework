#ifndef _AudioManager_H_
#define _AudioManager_H_

// TODO: Remove unecessary includes
#include "../../../QwerkE_Common/Libraries/OpenAL/include/al.h"
#include "../../../QwerkE_Common/Libraries/OpenAL/include/alc.h"

#include <vector>

//// create audio source object (sound player)
class AudioSource
{
public:
	AudioSource() { alGenSources(1, &m_Buffer); }
	~AudioSource() { alDeleteSources(1, &m_Buffer); }

	void Load(void* soundData) {}
	void Play(ALuint buffer);

	void SetOrientation(vec3 pos, vec3 rot, vec3 vel);

private:
	ALuint m_Buffer;
};

class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	void PlaySound();
	// music, effect, dialogue

	void SetListenerOrientation(vec3 position, vec3 velocity);

private:
	AudioSource* m_Source = nullptr;

	ALCdevice * Device;
	ALCcontext* Context;

	ALboolean g_bEAX; // Why?


	// buffer data
	const int NUM_BUFFERS = 1; // number of sound files
	std::vector<ALuint> m_SoundBuffers;
	ALboolean loop = AL_FALSE;
};

#endif // !_AudioManager_H_
