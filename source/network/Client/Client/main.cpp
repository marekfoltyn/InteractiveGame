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

    void pingCallback(RakNet::Packet*) {
        LOG("Callback!\n");
        exit(0);
    }
    
};

int main(int argc, const char * argv[]) {
    
    callback call;
    
    Connector * c = Connector::getInstance();
    c->startClient(CLIENT_PORT);
    
    c->addPacketCallback(PACKET_PING_REPLY, RAKNET_CALLBACK_1(callback::pingCallback, call));
    
    c->PingServers(SERVER_PORT);
    
    LOG("type whatever to exit\n");
    char ch;
    std::cin >> ch;
    
    return 0;
}

