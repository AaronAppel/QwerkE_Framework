#include "../../Core/Network/Network.h"

// https://github.com/facebookarchive/RakNet/tree/master/Samples
#include <stdio.h>
#include <cstdio>
#include <iostream>
#include <string.h>

#include "../../Libraries/RakNet/Source/RakPeerInterface.h"
#include "../../Libraries/RakNet/Source/RakNetTypes.h"
#include "../../Libraries/RakNet/Source/MessageIdentifiers.h"
#include "../../Libraries/RakNet/Source/BitStream.h"

#define MAX_CLIENTS 10
#define SERVER_PORT 60000

namespace QwerkE {

    std::string Network::m_IP = "127.0.0.1";
    RakNet::RakPeerInterface* m_Peer = nullptr;
    bool Network::m_IsServer = false;
    RakNet::Packet* m_Packet = nullptr;
    bool Network::m_Initialized = false;

    enum GameMessages
    {
        ID_GAME_MESSAGE_1 = ID_USER_PACKET_ENUM,
        // ID_GAME_MESSAGE_2...
    };

    void Network::Initialize()
    {
        char str[512];
        m_Peer = RakNet::RakPeerInterface::GetInstance();

        while (true)
        {
            printf("(C)lient or (S)erver?\n");
            std::cin >> str;

            if ((str[0] == 'c') || (str[0] == 'C'))
            {
                RakNet::SocketDescriptor sd;
                m_Peer->Startup(1, &sd, 1);
                m_IsServer = false;
                break;
            }
            else if ((str[0] == 's') || (str[0] == 'S'))
            {
                RakNet::SocketDescriptor sd(SERVER_PORT, 0);
                m_Peer->Startup(MAX_CLIENTS, &sd, 1);
                m_IsServer = true;
                break;
            }
        }

        if (m_IsServer)
        {
            StartServer();
        }
        else {
            ConnectToServer();
        }

        m_Initialized = true;
    }

    void Network::ConnectToServer()
    {
        char str[512];
        printf("Enter server IP or press enter to auto detect IP\n");
        std::cin >> str;
        // TODO: Error handling
        if (str[0] == 'a' || str[0] == 'A') {
            // strcpy_s(str, m_IP.c_str());
            // m_IP = m_Peer->GetLocalIP(0); // TODO: Get local IP address
        }
        printf("Starting the client.\n");
        m_Peer->Connect(m_IP.c_str(), SERVER_PORT, 0, 0); // TODO: Handle local and external IP addresses
    }

    void Network::DisconnectFromServer()
    {
        // TODO: Properly disconnect from host
        // m_Peer->GetMyGUID()
        // AddressOrGUID target = m_Peer->GetSystemAddressFromIndex(0);
        // m_Peer->CloseConnection(, true, 0, LOW_PRIORITY);
        m_Peer->Shutdown(0);
        RakNet::RakPeerInterface::DestroyInstance(m_Peer);
        m_Initialized = false;
        printf("You have disconnected.\n");
    }

    void Network::StartServer()
    {
        printf("Starting the server.\n");
        // We need to let the server accept incoming connections from the clients
        m_Peer->SetMaximumIncomingConnections(MAX_CLIENTS);
    }

    void Network::StopServer()
    {
        // TODO: Properly disconnect from host
        // m_Peer->GetMyGUID()
        // AddressOrGUID target = m_Peer->GetSystemAddressFromIndex(0);
        // m_Peer->CloseConnection(, true, 0, LOW_PRIORITY);
        m_Peer->Shutdown(0);
        RakNet::RakPeerInterface::DestroyInstance(m_Peer);
        m_Initialized = false;
        printf("Server has been stopped.\n");
    }

    void Network::TestUpdate()
    {
        if (!m_Initialized)
            return;

        for (m_Packet = m_Peer->Receive(); m_Packet; m_Peer->DeallocatePacket(m_Packet), m_Packet = m_Peer->Receive())
        {
            switch (m_Packet->data[0])
            {
            case ID_REMOTE_DISCONNECTION_NOTIFICATION:
                printf("Another client has disconnected.\n");
                break;
            case ID_REMOTE_CONNECTION_LOST:
                printf("Another client has lost the connection.\n");
                break;
            case ID_REMOTE_NEW_INCOMING_CONNECTION:
                printf("Another client has connected.\n");
                break;
            case ID_CONNECTION_REQUEST_ACCEPTED:
            {
                printf("Your connection request has been accepted.\n");

                // Use a BitStream to write a custom user message
                // Bitstreams are easier to use than sending casted structures, and handle endian swapping automatically
                RakNet::BitStream bsOut;
                bsOut.Write((RakNet::MessageID)ID_GAME_MESSAGE_1);
                bsOut.Write("Hello world");
                m_Peer->Send(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, m_Packet->systemAddress, false);
            }
            break;
            case ID_NEW_INCOMING_CONNECTION:
                printf("A connection is incoming.\n");
                break;
            case ID_NO_FREE_INCOMING_CONNECTIONS:
                printf("The server is full.\n");
                break;
            case ID_DISCONNECTION_NOTIFICATION:
                if (m_IsServer) {
                    printf("A client has disconnected.\n");
                }
                else {
                    printf("You have been disconnected.\n");
                }
                break;
            case ID_CONNECTION_LOST:
                if (m_IsServer) {
                    printf("A client lost the connection.\n");
                }
                else {
                    printf("Connection lost.\n");
                }
                break;
            case ID_GAME_MESSAGE_1:
            {
                RakNet::RakString rs;
                RakNet::BitStream bsIn(m_Packet->data, m_Packet->length, false);
                bsIn.IgnoreBytes(sizeof(RakNet::MessageID));
                bsIn.Read(rs);
                printf("%s\n", rs.C_String());
            }
            break;
            default:
                printf("Message with identifier %i has arrived.\n", m_Packet->data[0]);
                break;
            }
        }
    }

}
