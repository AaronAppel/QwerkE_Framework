#ifndef _Audio_Source_H_
#define _Audio_Source_H_

// TODO: Abstract from OpenAL
#include "../../Libraries/OpenAL/include/al.h"
#include "../Math/Vector.h"

namespace QwerkE {

    class AudioSource
    {
    public:
        AudioSource() { alGenSources(1, &m_SourceID); }
        ~AudioSource() { alDeleteSources(1, &m_SourceID); }

        void SetOrientation(vec3 pos, vec3 rot, vec3 vel);

        // TODO: Abstract from OpenAL
        void Play(ALuint buffer);

    private:
        // TODO: Abstract from OpenAL
        ALuint m_SourceID = 0;
    };

}
#endif // _Audio_Source_H_
