#pragma once

#include <vector>

#include "../../Libraries/OpenAL/include/al.h"
#include "../../Libraries/OpenAL/include/alc.h"

#include "../../Core/Audio/Audio.h"
#include "../../Core/Math/Vector.h"

namespace QwerkE {

    class AudioSource;

    class OpenALAudioManager : public Audio
    {
    public:
        ~OpenALAudioManager();

        bool Initialize();
        void Shutdown();

        void PlaySound(const char* name);
        // music, effect, dialogue

        void SetListenerOrientation(vec3 position, vec3 velocity);

    private:

        ALCdevice* m_Device = nullptr;
        ALCcontext* m_Context = nullptr;

        // ALboolean g_bEAX; // Why?

        // buffer data
        ALboolean loop = AL_FALSE;
        AudioSource* m_Source = nullptr;
    };

}
