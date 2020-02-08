#include "EventManager.h"
#include "../../QwerkE_Common/Utilities/PrintFunctions.h"
#include "../../QwerkE_Common/Utilities/Helpers.h"
#include "Event.h"

namespace QwerkE {

    const int EventManager::m_EventMax = 100;
    std::queue<Event*> EventManager::m_EventList;

    // EventManager::~EventManager()
       // m_EventList; // TODO: Delete events

    void EventManager::Initialize()
    {

    }

    void EventManager::QueueEvent(Event* _event)
    {
        // TODO: Implement thread safe API for multi threaded event queuing
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
            _event->Process();

            switch (_event->GetType())
            {
            case eEventTypes::eEvent_AssetLoaded:
                break;
            case eEventTypes::eEvent_JobQueued:
                break;
            case eEventTypes::eEvent_InputEvent:
                break;
            case eEventTypes::eEvent_Invalid:
                OutputPrint("\nEvent had invalid type!\n");
                break;
            default:
                OutputPrint("\nError reading event type!\nMake sure all types are handled.\n");
                break;
            }

            m_EventList.pop(); // Remove event from queue
        }
    }

}
