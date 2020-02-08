#include "Audio.h"
#include "OpenALAudioManager.h"

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

        ConsolePrint("\nAudio.PlaySound()\n");
    }

    void Audio::SetListenerOrientation(vec3 position, vec3 velocity)
    {
        if (m_Initialized)
            m_AudioManager->SetListenerOrientation(position, velocity);

        ConsolePrint("\SetListenerOrientation)\n");
    }

}
