#include "AudioSource.h"

#include "../../Libraries/OpenAL/include/al.h"
#include "../../QwerkE_Common/DataTypes/Vector.h"

namespace QwerkE {

    void AudioSource::SetOrientation(vec3 pos, vec3 rot, vec3 vel)
    {
        alSourcef(m_SourceID, AL_GAIN, 1.0f);
        alSourcef(m_SourceID, AL_PITCH, 1.0f);
        alSource3f(m_SourceID, AL_VELOCITY, vel.x, vel.y, vel.z);
        alSource3f(m_SourceID, AL_POSITION, 0.0f, 0.0f, 0.0f);
    }

    void AudioSource::Play(ALuint buffer)
    {
        alSourcei(m_SourceID, AL_LOOPING, AL_FALSE);
        alSourcei(m_SourceID, AL_BUFFER, buffer);
        alSourcePlay(m_SourceID);
    }

}
