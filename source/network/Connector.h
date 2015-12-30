#ifndef  _CONNECTOR_H_
#define  _CONNECTOR_H_

#include "raknet/MessageIdentifiers.h"
#include "raknet/RakPeerInterface.h"

/**
 @brief     Singleton class responsible for entire network communication.
 
 Represents both server and client
 
 usage: Connector::getInstance()-> ...
 
 */
class Connector {
public:
    
    static Connector * getInstance();
    
    bool startServer(int port);
    bool startClient(int port);
    
private:
    
    // Hidden singleton constructor
    Connector();
    
    // client/server mode
    bool isServer;
    
    // RakNet interface (for both client and server)
    RakNet::RakPeerInterface * rakInterface;
    
    // Singleton instance pointer
    static Connector * instance;
    
};

#endif // _CONNECTOR_H_