#include "EventManager.h"
#include "../QwerkE_Common/Utilities/PrintFunctions.h"
#include "../QwerkE_Common/Utilities/Helpers.h"
#include "Event.h"

EventManager::EventManager()
{
}

EventManager::~EventManager()
{
	m_EventList; // TODO: Delete events
}

void EventManager::QueueEvent(Event* _event)
{
	if (m_EventList.size() < m_EventMax)
	{
		_event->SetID(helpers_GetUniqueID());
		m_EventList.push(_event);
		OutputPrint("Event %i Queued!", _event->GetID());
	}
	else
	{
		OutputPrint("Event list is full!");
	}
}

void EventManager::ProcessEvents()
{
	int size = m_EventList.size();

	for (int i = 0; i < size; i++)
	{
		Event* _event = m_EventList.front();

		switch (_event->GetType())
		{
		case eEventTypes::eEvent_Invalid:
			OutputPrint("\nEvent had invalid type!\n");
			break;
		default:
			OutputPrint("\nError reading event type!\nMake sure all types are handled.\n");
			break;
		}

		m_EventList.pop();
	}
}