#ifndef _EventManager_H_
#define _EventManager_H_

#include <queue>

class Event;

namespace QwerkE {

    class EventManager
    {
    public:
        EventManager();
        ~EventManager();

        void QueueEvent(Event* _event);

        void ProcessEvents();

        // register callbacks/listeners

    private:
        const int m_EventMax = 100;
        // eventlist
        std::queue<Event*> m_EventList;
    };

}
#endif //!_EventManager_H_
