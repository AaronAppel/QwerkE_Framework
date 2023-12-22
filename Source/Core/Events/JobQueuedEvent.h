#pragma once

#include "Event.h"
#include "../Graphics/DataTypes/Texture.h"

namespace QwerkE {

    class JobQueuedEvent : public Event
    {
    public:
        JobQueuedEvent();
        ~JobQueuedEvent();

        void Process();
    };

}

