#include "JobQueuedEvent.h"
#include "../Resources/Resources.h"
#include "../../Headers/QwerkE_Enums.h"

namespace QwerkE {

    JobQueuedEvent::JobQueuedEvent()
    {
        m_EventType = eEventTypes::eEvent_JobQueued;
    }

    JobQueuedEvent::~JobQueuedEvent()
    {
    }

    void JobQueuedEvent::Process()
    {
        Jobs::ProcessTasks();
    }

}
