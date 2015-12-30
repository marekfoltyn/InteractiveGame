#include "Connector.h"

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
    isServer = false;
}

/**
 *  Starts a server
 */
bool Connector::startServer(int port){
    isServer = true;
    
    
    
    
    return true;
}

/**
 *  Starts a client
 */
bool Connector::startClient(int port){
    isServer = false;
    
    
    
    
    return true;
}
