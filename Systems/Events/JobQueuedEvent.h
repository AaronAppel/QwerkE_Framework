#ifndef _JobQueuedEvent_H_
#define _JobQueuedEvent_H_

#include "Event.h"
#include "../../Graphics/Texture.h"

class JobQueuedEvent: public Event
{
public:
	JobQueuedEvent();
    ~JobQueuedEvent();

	void Process();
};

#endif // !_AssetLoadedEvent_H_
