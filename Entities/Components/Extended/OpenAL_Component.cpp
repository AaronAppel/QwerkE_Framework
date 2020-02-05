#include "OpenAL_Component.h"
#include "../../../Systems/Services.h"
#include "../../../Systems/ResourceManager/ResourceManager.h"

namespace QwerkE {

    OpenAL_AudioComponent::OpenAL_AudioComponent()
        : m_Buffer(Services::Resources.GetSound(null_sound))
    {
    }

    OpenAL_AudioComponent::~OpenAL_AudioComponent()
    {
    }

    int OpenAL_AudioComponent::Play()
    {
        alSourcePlay(m_Buffer);
        return 1;
    }

}
