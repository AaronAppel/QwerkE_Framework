#include "AudioSource.h"

AudioSource::AudioSource()
{
	alGenSources(1, &m_Buffer);
}

AudioSource::~AudioSource()
{
	alDeleteSources(1, &m_Buffer);
}

void AudioSource::SetOrientation(vec3 pos, vec3 rot, vec3 vel)
{
	alSourcef(m_Buffer, AL_GAIN, 0.2f);
	alSourcef(m_Buffer, AL_PITCH, 1.0f);
	alSource3f(m_Buffer, AL_VELOCITY, vel.x, vel.y, vel.z);
	alSource3f(m_Buffer, AL_POSITION, 0.0f, 0.0f, 0.0f);
}
void AudioSource::Play(ALuint buffer)
{
	alSourcei(m_Buffer, AL_LOOPING, AL_FALSE);
	alSourcei(m_Buffer, AL_BUFFER, buffer);
	alSourcePlay(m_Buffer);
}