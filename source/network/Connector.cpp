#include "Connector.h"
#include "Definitions.h"

#include "raknet/MessageIdentifiers.h"
#include "raknet/RakPeerInterface.h"
#include "raknet/RakPeerInterface.h"
#include "raknet/RakNetTypes.h"
#include "raknet/GetTime.h"
#include "raknet/BitStream.h"
#include "raknet/RakSleep.h"

#include <assert.h>
#include <cstdio>
#include <cstring>
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

void Connector::PingServers(int timeoutMS){
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
        } else {
            p = client->Receive();
        }
        
        if (p==0)
        {
            RakSleep(RAKNET_SLEEP);
            continue;
        }
        
        // find appropriate callback function
        auto found = callbackMap.find(p->data[0]);
        if( found != callbackMap.end() ){
            //callbackMap[p->data[0]](p->data+1,p->bitSize/8-1);
        }
        
        if (p->data[0]==ID_UNCONNECTED_PONG){
            
            RakNet::TimeMS time;
            RakNet::BitStream bsIn(p->data,p->length,false);
            bsIn.IgnoreBytes(1);
            bsIn.Read(time);
            LOG("Got pong from %s with time %i\n", p->systemAddress.ToString(), RakNet::GetTimeMS() - time);
            
        } else if (p->data[0]==ID_UNCONNECTED_PING){
            
            LOG("ID_UNCONNECTED_PING from %s\n",p->guid.ToString());
        
        } else if (p->data[0]==ID_UNCONNECTED_PING_OPEN_CONNECTIONS){
            
            LOG("ID_UNCONNECTED_PING_OPEN_CONNECTIONS from %s\n",p->guid.ToString());
        
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

void Connector::addPacketCallback(int packetType, callbackFuncType callback ){
    
    callbackMap[packetType] = callback;
    
}


void Connector::removePacketCallback(int packetType){
    
    callbackMap.erase(packetType);
    
    
}

