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

    static void pingCallback(){
        LOG("Callback!\n");
    }
    
};

int main(int argc, const char * argv[]) {
    
    Connector * c = Connector::getInstance();
    c->startClient(52589);
    
    //TODO: vyresit RakNet namespace
    c->addPacketCallback(RakNet::ID_UNCONNECTED_PONG, callback::pingCallback());
    
    c->PingServers(4000);
    
    LOG("type whatever to exit\n");
    char ch;
    std::cin >> ch;
    
    return 0;
}

