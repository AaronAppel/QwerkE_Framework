#pragma once

#include "Component.h"

namespace QwerkE {

    class AudioComponent : public Component
    {
    public:
        virtual ~AudioComponent() {};

        virtual int Play() = 0;
    };

}
