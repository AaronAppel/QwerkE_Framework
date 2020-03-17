#ifndef _Network_H_
#define _Network_H_

#include <string>

// TODO: Remove #includes
#include "../../Libraries/RakNet/Source/RakPeerInterface.h"
#include "../../Libraries/RakNet/Source/RakNetTypes.h"
// class RakNet::RakPeerInterface;
// class RakNet::Packet;

namespace QwerkE {

    class Network
    {
    public:
        static void Initialize();
        static void TearDown();

        static void TestUpdate();

    private:
        Network() {}
        ~Network() {}

        static std::string m_IP;
        static RakNet::RakPeerInterface* m_Peer;
        static RakNet::Packet* m_Packet;
        static bool m_IsServer;
        static bool m_Initialized;
    };

}
#endif // _Network_H_
