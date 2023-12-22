#pragma once

#include "../Math/Vector.h"

namespace QwerkE {

    class OpenALAudioManager;

    class Audio
    {
    public:
        static bool Initialize();
        static void Shutdown();

        static void PlaySound(const char* name);

        static void SetListenerOrientation(vec3 position, vec3 velocity);

        static bool Initialized() { return m_Initialized; }

    protected:
        Audio() {}
        ~Audio() {}

    private:
        static bool m_Initialized;

        // #TODO Abstract from OpenAL
        static OpenALAudioManager* m_AudioManager;
    };

}

