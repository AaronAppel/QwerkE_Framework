#include "JobQueuedEvent.h"
#include "../ResourceManager/ResourceManager.h"
#include "../ServiceLocator.h"

JobQueuedEvent::JobQueuedEvent()
{
    m_EventType = eEventTypes::eEvent_JobQueued;
}

JobQueuedEvent::~JobQueuedEvent()
{
}

void JobQueuedEvent::Process()
{
	((JobManager*)QwerkE::ServiceLocator::GetService(eEngineServices::JobManager))->ProcessTasks();
}