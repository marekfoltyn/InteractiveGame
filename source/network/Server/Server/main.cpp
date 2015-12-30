//
//  main.cpp
//  Server
//
//  Created by Marek Foltýn on 30.12.15.
//  Copyright © 2015 foltyma1. All rights reserved.
//

#include <iostream>
#include "Connector.h"

int main(int argc, const char * argv[]) {
    
    Connector * c = Connector::getInstance();
    c->startServer(54000);
    
    return 0;
}
