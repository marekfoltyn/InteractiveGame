#ifndef  _CONNECTOR_H_
#define  _CONNECTOR_H_

#include "MessageIdentifiers.h"
#include "RakPeerInterface.h"
#include "Definitions.h"
#include "GameplayEvents.h"
#include "Box.h"
#include <string>

/**
 * Networking library for client-server game connection
 */
namespace GameNet{

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
    bool startAsClient();
    
    /** starts a server network session
     * @return true if started, false otherwise
     */
    bool startAsServer(unsigned short maxPlayers=MAX_PLAYERS);
    
    /**
     * stop networking (on app exit)
     */
    void stop();
    
    /** 
     * connect to a server
     * don't use if startAsServer() was called!
     */
    void connect( RakNet::SystemAddress server );
    
    /**
     * disconnect from the address
     * ignored if not connected
     */
    void disconnect( RakNet::SystemAddress address );
    
    /**
     * send a Box (It is a wrapped RakNet::Packet with some additional data)
     */
    void send(Box * b);
    
    /**
     * receive a packet from received packet queue (non-boxing way) and create a Box
     * @return: pointer to Box (need to deallocate when done with it), 0 if no packet is the queue
     */
    Box * receive();
    
    /**
     * get/set server name
     * if the Connector is not started as a server, does nothing / returns default server name
     */
    void setServerName(std::string name);
    std::string getServerName();
    
    /**
     * Ping all servers that are not full
     */
    void ping();

    
    /**
     * If the instance of Connector is a client, returns the address
     * of the server the Connector is connected to, otherwise returns RakNet::UNASSIGNED_SYSTEM_ADDRESS
     */
    RakNet::SystemAddress getServer();
    
    /**
     * get RakNet interface
     * only for Connector framework purposes, shouldn't be used in game
     */
    RakNet::RakPeerInterface * getInterface(){return raknetInterface;};
        
private:
    
    /**
     * Hidden singleton constructor
     */
    Connector();
    
    /**
     * RakNet interface
     */
    RakNet::RakPeerInterface * raknetInterface = nullptr;
    
    /**
     * Singleton instance pointer
     */
    static Connector * instance;
    
    /**
     * server address (used only by a client?)
     */
    RakNet::SystemAddress server;
    
};
    
}
#endif // _CONNECTOR_H_