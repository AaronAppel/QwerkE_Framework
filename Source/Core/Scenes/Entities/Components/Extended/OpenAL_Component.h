#pragma once

#include "../../../../../../Libraries/OpenAL/include/al.h"

#include "../AudioComponent.h"

namespace QwerkE {

    class OpenAL_AudioComponent : public AudioComponent
    {
    public:
        OpenAL_AudioComponent();
        ~OpenAL_AudioComponent();

        int Play();

    private:
        ALuint m_Buffer = 0;
    };

}
