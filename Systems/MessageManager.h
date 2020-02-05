#ifndef _MessageManager_H_
#define _MessageManager_H_

// handles all messages from external code like
// networking, shared memory, and threading.
// Works with logger.

// provides global API for sending and receiving messages

namespace QwerkE {

    class MessageManager
    {
    public:
        MessageManager();
        ~MessageManager();

    private:

    };

}

#endif // !_MessageManager_H_
