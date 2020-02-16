#ifndef _JobQueuedEvent_H_
#define _JobQueuedEvent_H_

#include "Event.h"
#include "../../Graphics/DataTypes/Texture.h"

namespace QwerkE {

    class JobQueuedEvent : public Event
    {
    public:
        JobQueuedEvent();
        ~JobQueuedEvent();

        void Process();
    };

}
#endif // _JobQueuedEvent_H_
