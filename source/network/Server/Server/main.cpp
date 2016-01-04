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

int main(int argc, const char * argv[]) {
    
    
    Connector * c = Connector::getInstance();
    c->startServer(SERVER_PORT);
    
    return 0;
}
