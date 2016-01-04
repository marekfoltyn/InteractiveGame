#ifndef  _CONNECTOR_H_
#define  _CONNECTOR_H_

#include "raknet/MessageIdentifiers.h"
#include "raknet/RakPeerInterface.h"
#include "raknet/RakSleep.h"
#include <thread>
#include <map>

// callback function type for packet processing
typedef void(*callbackFuncType)(void);

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
    
    void stopServer();
    void stopClient();
    
    // add callback to packet type
    void addPacketCallback(int packetType, callbackFuncType );
    void removePacketCallback(int packetType);
    
    //// Client ////
    void PingServers(int timeoutMS);
    
private:
    
    // Hidden singleton constructor
    Connector();
    
    // Packet processing runnable for packetProcessor thread
    void infiniteReceiveLoop();
    
    // PacketProcessor control
    void startPacketProcessor();
    void stopPacketProcessor();
    
    // RakNet interfaces
    RakNet::RakPeerInterface * server = nullptr;
    RakNet::RakPeerInterface * client = nullptr;
    
    // Singleton instance pointer
    static Connector * instance;
    
    std::thread packetProcessorThread;
    
    // Map of callback functions for packet types
    std::map<int, callbackFuncType> callbackMap;
    
    // If true, receive loop will continue; if false, loop finishes before next loop
    bool loopIsActive;
    
};

#endif // _CONNECTOR_H_