#include "EventManager.h"
#include "Event.h"
#include "../../Utilities/Helpers.h"
#include "../../Debug/Log/Log.h"

#include <pThreads/pthread.h>

namespace QwerkE {

    // TODO: Make QueueEvent() thread safe
    static pthread_mutex_t* mutex = nullptr;
    const int EventManager::m_EventMax = 100;
    std::queue<Event*> EventManager::m_EventList;

    // EventManager::~EventManager()
       // m_EventList; // TODO: Delete events

    void EventManager::Initialize()
    {
        mutex = new pthread_mutex_t();
    }

    void EventManager::Shutdown()
    {
        delete mutex;
    }

    void EventManager::QueueEvent(Event* _event)
    {
        // pthread_mutex_lock(mutex);
        // TODO: Implement thread safe API for multi threaded event queuing
        if (m_EventList.size() < m_EventMax)
        {
            _event->SetID(helpers_GetUniqueID());
            m_EventList.push(_event);
            LOG_INFO("Event {0} Queued!", _event->GetID());
        }
        else
        {
            LOG_ERROR("Event list is full!");
        }
        // pthread_mutex_unlock(mutex);
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
                LOG_ERROR("Invalid event type found!");
                break;
            default:
                LOG_ERROR("Error reading event type. Make sure all types are handled!");
                break;
            }

            m_EventList.pop(); // Remove event from queue
        }
    }

}
