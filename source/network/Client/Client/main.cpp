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
        
        /*
        // Peer or client. Response from a ping for an unconnected system.
        RakNet::TimeMS packetTime, dataLength;
        RakNet::TimeMS curTime = RakNet::GetTimeMS();
        RakNet::BitStream bsIn(packet->data,packet->length,false);
        bsIn.IgnoreBytes(1);
        bsIn.Read(packetTime);
        dataLength = packet->length - sizeof( unsigned char ) - sizeof( RakNet::TimeMS );
         */
        
        //TODO: osetrit format paketu (idealne na strane Connectoru
        
        LOG("Received data length in bytes: %d\n", p->length);
        LOG("Data: %s\n", p->data+5);
        Connector::getInstance()->addPacketCallback(PACKET_SERVER_NAME, RAKNET_CALLBACK_1(callback::serverNameCallback, this));
        
        //Connector::getInstance()->FindServerName(p->systemAddress);
        
        //exit(0);
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

