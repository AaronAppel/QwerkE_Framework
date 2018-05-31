#ifndef _AudioSource_H_
#define _AudioSource_H_

#include "../../QwerkE_Common/Libraries/OpenAL/include/al.h"

class AudioSource
{
public:
	AudioSource() { alGenSources(1, &m_SourceID); }
	~AudioSource() { alDeleteSources(1, &m_SourceID); }

	void SetOrientation(vec3 pos, vec3 rot, vec3 vel);

	void Play(ALuint buffer);

private:
	ALuint m_SourceID = 0;
};

#endif // !_AudioSource_H_
