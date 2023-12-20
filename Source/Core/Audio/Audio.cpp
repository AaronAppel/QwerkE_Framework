#include "Audio.h"

#include "../../Debug/Log/Log.h"

#include "OpenALAudioManager.h"
#include "../Math/Vector.h"

namespace QwerkE {

    OpenALAudioManager* Audio::m_AudioManager = nullptr;
    bool Audio::m_Initialized = false;

    void Audio::Initialize()
    {
        m_AudioManager = new OpenALAudioManager();
        m_Initialized = true;
    }

    void Audio::Shutdown()
    {
        m_Initialized = false;
        delete m_AudioManager;
    }

    void Audio::PlaySound(const char* name)
    {
        if (m_Initialized)
            m_AudioManager->PlaySound(name);
        else
            Log::Trace("Audio.PlaySound()");
    }

    void Audio::SetListenerOrientation(vec3 position, vec3 velocity)
    {
        if (m_Initialized)
            m_AudioManager->SetListenerOrientation(position, velocity);
        else
            Log::Trace("Audio.SetListenerOrientation()");
    }

}
