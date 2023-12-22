#pragma once

#include "Component.h"

class AudioSource;

namespace QwerkE {

    class AudioComponent : public Component // abstract
    {
    public:
        virtual ~AudioComponent() {};

        virtual int Play() = 0;
    };

}
