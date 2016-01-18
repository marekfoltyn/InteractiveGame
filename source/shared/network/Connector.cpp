#include "Connector.h"
#include "Definitions.h"

#include "MessageIdentifiers.h"
#include "RakPeerInterface.h"
#include "RakNetTypes.h"
#include "GetTime.h"
#include "BitStream.h"
#include "RakSleep.h"

#include <assert.h>
#include <cstdio>
#include <cstring>
#include <string>
#include <stdlib.h>

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
Connector::Connector(){
    loopIsActive = false;
}

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
    bool b = server->Startup(MAX_PLAYERS, socketDescriptors, 1 )==RakNet::RAKNET_STARTED;
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
    server->SetUnreliableTimeout(CONNECTION_LOST_TIMEOUT);
    
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
    
    
    server->SetOfflinePingResponse("Unnamed Server", strlen("Unnamed Server")+1);
    
    startPacketProcessor();

    return true;
}

/**
 * Stops the client
 */
void Connector::stopServer(){
    if(server != nullptr){
        stopPacketProcessor();
        RakNet::RakPeerInterface::DestroyInstance(server);
        server = nullptr;
    }
}

void Connector::setServerName(const char * name, int len){
    if(server == nullptr){
        return;
    }
    
    server->SetOfflinePingResponse(name, len);
}
std::string Connector::getServerName(){
    if(server == nullptr){
        LOG("Server not started - no name!");
        return "";
    }
    
    char * name;
    unsigned int len;
    server->GetOfflinePingResponse(&name, &len);
    
    return name;
    
}


/**
 *  Starts a client
 */
bool Connector::startClient(int port){
    
    client = RakNet::RakPeerInterface::GetInstance();
    RakNet::SocketDescriptor socketDescriptor( port, 0 );
    socketDescriptor.socketFamily = AF_INET; // Only IPV4 supports broadcast on 255.255.255.255
    auto b = client->Startup(1, &socketDescriptor, 1);
    if(b != RakNet::RAKNET_STARTED){
        LOG("Client start failed.");
        return false;
    }
    
    LOG("\nMy IP addresses:\n");
    
    unsigned int i;
    for (i=0; i < client->GetNumberOfAddresses(); i++)
    {
        LOG("%i. %s\n", i+1, client->GetLocalIP(i));
    }
    
    startPacketProcessor();
    
    return true;
}

/**
 *  Stops the client
 */
void Connector::stopClient(){
    if(client != nullptr){
        stopPacketProcessor();
        RakNet::RakPeerInterface::DestroyInstance(client);
        client = nullptr;
    }
}

void Connector::connect(RakNet::SystemAddress serverAddress){
    if(client==nullptr){
        LOG("Client is not started!");
        return;
    }
    
    char ip[4];
    serverAddress.ToString(false, ip);
    
    client->Connect(ip, serverAddress.GetPort(), NULL, 0);
}


void Connector::FindServers(){
    if(client==nullptr){
        LOG("Client is not started!");
        return;
    }
    
    client->Ping("255.255.255.255", SERVER_PORT, false);
    LOG("Pinging\n");
    
}

void Connector::infiniteReceiveLoop(){
    
    LOG("infiniteReceiveLoop started!\n");
    
    while (loopIsActive){
        
        RakNet::Packet * p;
        
        // receive packet
        if (server){
            p = server->Receive();
        } else if(client) {
            p = client->Receive();
        } else {
            return;
        }
                
        if (p==0)
        {
            RakSleep(RAKNET_SLEEP);
            continue;
        }
        
        // call appropriate callback function, if exists
        auto found = callbackMap.find(p->data[0]);
        if( found != callbackMap.end() ){
            callbackMap[p->data[0]](p);
        }
        
        if(client == nullptr){
            server->DeallocatePacket(p);
        } else {
            client->DeallocatePacket(p);
        }
        
        RakSleep(30);
    }
    
}

void Connector::startPacketProcessor(){
    loopIsActive = true;
    packetProcessorThread = std::thread(&Connector::infiniteReceiveLoop,this);
    packetProcessorThread.detach();
}

void Connector::stopPacketProcessor(){
    loopIsActive = false;
}

void Connector::addPacketCallback(int packetType, const CALLBACK_TYPE& callback ){
    callbackMap[packetType] = callback;
}


void Connector::removePacketCallback(int packetType){
    
    callbackMap.erase(packetType);
    
    
}
