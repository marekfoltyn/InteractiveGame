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
    server->SetIncomingPassword(INCOMING_PASSWORD, strlen(INCOMING_PASSWORD));
    
    LOG("Starting server.\n");
    
    // Starting the server is very simple.
    // 0 means we don't care about a connectionValidationInteger, and false
    // for low priority threads.
    
    RakNet::SocketDescriptor socketDescriptors[1];
    socketDescriptors[0].port = port;
    socketDescriptors[0].socketFamily=AF_INET; // IPV4
    bool b = server->Startup(4, socketDescriptors, 1 )==RakNet::RAKNET_STARTED;
    server->SetMaximumIncomingConnections(4);
    if (!b)
    {
        LOG("Server failed to start.");
        RakNet::RakPeerInterface::DestroyInstance(server);
        server = nullptr;
        return false;
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
 * Stops the client
 */
void Connector::stopServer(){
    if(server != nullptr){
        RakNet::RakPeerInterface::DestroyInstance(server);
        server = nullptr;
    }
}

/**
 *  Starts a client
 */
bool Connector::startClient(int port){
    
    client = RakNet::RakPeerInterface::GetInstance();
    RakNet::SocketDescriptor socketDescriptor( port, 0 );
    socketDescriptor.socketFamily = AF_INET; // Only IPV4 supports broadcast on 255.255.255.255
    bool b = client->Startup(1, &socketDescriptor, 1);
    if(!b){
        LOG("Client start failed.");
        return false;
    }
    
    LOG("\nMy IP addresses:\n");
    
    unsigned int i;
    for (i=0; i < client->GetNumberOfAddresses(); i++)
    {
        printf("%i. %s\n", i+1, client->GetLocalIP(i));
    }
    
    return true;
}

/**
 *  Stops the client
 */
void Connector::stopClient(){
    if(client != nullptr){
        RakNet::RakPeerInterface::DestroyInstance(client);
        client = nullptr;
    }
}