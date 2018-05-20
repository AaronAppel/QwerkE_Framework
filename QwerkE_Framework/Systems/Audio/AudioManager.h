#ifndef _AudioManager_H_
#define _AudioManager_H_

#include "../../../QwerkE_Common/Libraries/OpenAL/include/al.h"
#include "../../../QwerkE_Common/Libraries/OpenAL/include/alc.h"

#include <vector>

class AudioSource;

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
