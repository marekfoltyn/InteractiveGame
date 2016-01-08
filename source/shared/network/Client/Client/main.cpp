//
//  main.cpp
//  Client
//
//  Created by Marek Foltýn on 30.12.15.
//  Copyright © 2015 foltyma1. All rights reserved.
//

#include <iostream>
#include "Connector.h"
#include "Definitions.h"

using namespace std::placeholders;

class callback{
    public:

    void pingCallback(RakNet::Packet * p) {
        
        // Peer or client. Response from a ping for an unconnected system.
        // Ping response has this format: MessageType(1B)+TimeMS(4B)+ServerName(the rest of Bytes)
        RakNet::TimeMS packetTime;
        RakNet::TimeMS curTime = RakNet::GetTimeMS();
        RakNet::BitStream bsIn(p->data,p->length,false);
        bsIn.IgnoreBytes(1);
        bsIn.Read(packetTime);
        
        // osetrit format paketu na strane Connectoru?
        
        LOG("New server: %s (%dms)\n", p->data + sizeof(unsigned char) + sizeof(RakNet::TimeMS), curTime );
        
        Connector::getInstance()->addPacketCallback(PACKET_SERVER_NAME, RAKNET_CALLBACK_1(callback::serverNameCallback, this));
        
        exit(0);
    }
    
    void serverNameCallback(RakNet::Packet * p){
        LOG("Server name: %s\n", p->data+1);
        exit(0);
    }
    
};

int main(int argc, const char * argv[]) {
    
    callback call;
    
    Connector * c = Connector::getInstance();
    c->startClient(CLIENT_PORT);
    
    c->addPacketCallback(PACKET_SERVER_FOUND, RAKNET_CALLBACK_1(callback::pingCallback, call));
    
    c->PingServers(SERVER_PORT);
    
    LOG("type whatever to exit\n");
    char ch;
    std::cin >> ch;
    
    return 0;
}

