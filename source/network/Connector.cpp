#include "Connector.h"
#include "Definitions.h"

// initialize static variable
Connector * Connector::instance = nullptr;

// getting singleton instance
Connector * Connector::getInstance(){

    if(instance == nullptr) {
        instance = new Connector();
    }
    return instance;
}

/**
 *  Constructor, now does nothing
 */
Connector::Connector(){}

/**
 *  Starts a server
 */
bool Connector::startServer(int port){

    server = RakNet::RakPeerInterface::GetInstance();
    server->SetTimeoutTime(CONNECTION_LOST_TIMEOUT, RakNet::UNASSIGNED_SYSTEM_ADDRESS);
    
    LOG("Starting server.");
    
    // Starting the server is very simple.
    // 0 means we don't care about a connectionValidationInteger, and false
    // for low priority threads.
    // Creating two socketDesciptors, to create two sockets. One using IPV6 and the other IPV4
    RakNet::SocketDescriptor socketDescriptors[2];
    socketDescriptors[0].port = port;
    socketDescriptors[0].socketFamily=AF_INET; // Test out IPV4
    socketDescriptors[1].port = port;
    socketDescriptors[1].socketFamily=AF_INET6; // Test out IPV6
    bool b = server->Startup(4, socketDescriptors, 2 )==RakNet::RAKNET_STARTED;
    server->SetMaximumIncomingConnections(4);
    if (!b)
    {
        LOG("Failed to start dual IPV4 and IPV6 ports. Trying IPV4 only.\n");
        
        // Try again, but leave out IPV6
        b = server->Startup(4, socketDescriptors, 1 )==RakNet::RAKNET_STARTED;
        if (!b)
        {
            LOG("Server failed to start.");
            return false;
        }
    }
    LOG("\n");
    
    server->SetOccasionalPing(true);
    server->SetUnreliableTimeout(1000);
    
    DataStructures::List< RakNet::RakNetSocket2* > sockets;
    server->GetSockets(sockets);
    LOG("Socket addresses used by RakNet:\n");
    for (unsigned int i=0; i < sockets.Size(); i++)
    {
        LOG("%i. %s\n", i+1, sockets[i]->GetBoundAddress().ToString(true));
    }
    
    LOG("\nMy IP addresses:\n");
    for (unsigned int i=0; i < server->GetNumberOfAddresses(); i++)
    {
        RakNet::SystemAddress sa = server->GetInternalID(RakNet::UNASSIGNED_SYSTEM_ADDRESS, i);
        LOG("%i. %s:%i\n", i+1, sa.ToString(false), sa.GetPort());
    }
    
    return true;
}

/**
 *  Starts a client
 */
bool Connector::startClient(int port){
    
    
    
    
    return true;
}
