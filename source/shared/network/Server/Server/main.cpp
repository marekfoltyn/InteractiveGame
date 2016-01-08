//
//  main.cpp
//  Server
//
//  Created by Marek Foltýn on 30.12.15.
//  Copyright © 2015 foltyma1. All rights reserved.
//

#include <iostream>
#include "Connector.h"
#include "Definitions.h"

class Callbacker{
public:
    void pingCallback(RakNet::Packet* p){
        LOG("received ping from %s\n", p->systemAddress.ToString());
    }
};

int main(int argc, const char * argv[]) {
    
    Callbacker call;
    
    Connector * c = Connector::getInstance();
    c->addPacketCallback(PACKET_FIND_SERVER, RAKNET_CALLBACK_1(Callbacker::pingCallback, call));
    c->startServer(SERVER_PORT);
    
    c->setServerName("Debug Server v0.1", strlen("Debug Server v0.1")+1); // proper C string ending
    
    LOG("type whatever to exit\n");
    char ch;
    std::cin >> ch;
    
    return 0;
}
