#ifndef _AudioSource_H_
#define _AudioSource_H_

#include "../../../QwerkE_Common/Libraries/OpenAL/include/al.h"

// sound player class
class AudioSource
{
public:
	AudioSource();
	~AudioSource();

	void Load(void* soundData) {}
	void Play(ALuint buffer);

	void SetOrientation(vec3 pos, vec3 rot, vec3 vel);

private:
	ALuint m_Buffer;
};

#endif // !_AudioSource_H_
