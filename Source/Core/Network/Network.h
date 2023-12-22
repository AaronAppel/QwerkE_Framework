#pragma once

#include <string>

namespace QwerkE {

    class Network
    {
    public:
        static void Initialize();
        static void TearDown() {};

        static void TestUpdate();

        static void ConnectToServer();
        static void DisconnectFromServer();

        static void StartServer();
        static void StopServer();

        static bool IsInitialized() { return m_Initialized; }
        static bool IsServer() { return m_IsServer; }

    private:
        Network() {}
        ~Network() {}

        static std::string m_IP;
        static bool m_IsServer;
        static bool m_Initialized;
    };

}
