#ifndef  _CONNECTOR_H_
#define  _CONNECTOR_H_

#include "MessageIdentifiers.h"
#include "RakPeerInterface.h"

/**
 * @brief     Singleton class responsible for entire network communication.
 * Represents network interface (both server and client)
 * usage: Connector::getInstance()-> ...
 */
class Connector {
public:
    
    /**
     * get singleton instance
     */
    static Connector * getInstance();
    
    /** starts a client network session
     * @return true if started, false otherwise
     */
    bool start();
    
    /** starts a server network session
     * @return true if started, false otherwise
     */
    bool startAsServer(unsigned short maxPlayers);
    
    /**
     * stop networking (app exit)
     */
    void stop();
    
    /** 
     * connect to a server
     */
    void connect( RakNet::SystemAddress server );
    
    /**
     * disconnect from the address
     * ignored if not connected
     */
    void disconnect( RakNet::SystemAddress address );
    
    /**
     * send a Block (It is a wrapped RakNet::Packet with some additional data)
     */
    void send(Block * b);
    
    /**
     * receive a packet from received packet queue (non-blocking way)
     * @return: pointer to  packet (need to deallocate when done with it), 0 if no packet is the queue
     */
    RakNet::Packet * receive();
    
    /**
     * get/set server name (if startAsServer() was called before)
     */
    void setServerName(std::string name);
    std::string getServerName();
    
    /**
     * Ping all servers that are not full
     */
    void ping();
        
private:
    
    // Hidden singleton constructor
    Connector(){};
    
    // RakNet interface
    RakNet::RakPeerInterface * interface = nullptr;
    
    // Singleton instance pointer
    static Connector * instance;
    
};

#endif // _CONNECTOR_H_