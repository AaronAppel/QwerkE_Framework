#ifndef _EventManager_H_
#define _EventManager_H_

#include <queue>

namespace QwerkE {

    class Event;

    class EventManager
    {
    public:
        static void Initialize();
        static void Shutdown();

        static void QueueEvent(Event* _event);

        static void ProcessEvents();

        // Register callbacks/listeners

    private:
        EventManager() {}
        ~EventManager() {}

        static const int m_EventMax;
        static std::queue<Event*> m_EventList;
    };

}
#endif //!_EventManager_H_
