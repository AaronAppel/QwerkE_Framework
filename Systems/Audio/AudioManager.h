#ifndef _AudioManager_H_
#define _AudioManager_H_

#include "../../QwerkE_Common/Libraries/OpenAL/include/al.h"
#include "../../QwerkE_Common/Libraries/OpenAL/include/alc.h"
#include "../../QwerkE_Common/DataTypes/Vector.h"

#include <vector>

class AudioSource;

class AudioManager
{
public:
	AudioManager();
	~AudioManager();

	void PlaySound(const char* name);
	// music, effect, dialogue

	void SetListenerOrientation(vec3 position, vec3 velocity);

private:

	ALCdevice* Device;
	ALCcontext* Context;

	// ALboolean g_bEAX; // Why?

	// buffer data
	ALboolean loop = AL_FALSE;
	AudioSource* m_Source = nullptr;
};

#endif // !_AudioManager_H_
