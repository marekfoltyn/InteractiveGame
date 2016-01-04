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

class callback{
    public:

    static void pingCallback(unsigned char * data, int byteCount){
        LOG("Callback!\n");
        exit(0);
    }
    
};

int main(int argc, const char * argv[]) {
    
    Connector * c = Connector::getInstance();
    c->startClient(CLIENT_PORT);
    
    //TODO: vyresit RakNet namespace
    c->addPacketCallback(PACKET_PING_REPLY, callback::pingCallback);
    
    c->PingServers(SERVER_PORT);
    
    LOG("type whatever to exit\n");
    char ch;
    std::cin >> ch;
    
    return 0;
}

