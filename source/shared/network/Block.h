#ifndef  _BLOCK_H_
#define  _BLOCK_H_

#include "MessageIdentifiers.h"
#include "RakPeerInterface.h"
#include "RakSleep.h"
#include "GetTime.h"
#include "BitStream.h"

#include <thread>
#include <map>

/**
 * Representation of game message to be sent to network.
 * Block also includes information about packet - type, reliability, priority, ordering, address, ...
 * Example:
 *
 * Block * b;
 *
 * ... // init, fill with data, adress and so on...
 *
 * Connector::getInstance()->send(b);
 */
class Block {
public:
    
    /**
     * create a Block and copies data so the data has to be freed manually
     * @param byteSize size of the data
     */
    static Block * create(const char * data, unsigned int len );

    /**
     * set packet type (defined in Definitions.h)
     */
    void setType(unsigned char type);
    
    /**
     * get packet type (defined in Definitions.h)
     */
    unsigned char getType();
    
    /**
     * set RakNet packet reliability
     */
    void setReliability( PacketReliability r );
    
    /**
     * get RakNet packet reliability
     */
    PacketReliability getReliability();
    
    /**
     * set RakNet packet send priority
     */
    void setPriority( PacketPriority p );
    
    /**
     * get RakNet packet send priority
     */
    PacketPriority getPriority();

    /**
     * set RakNet system address the Block should be sent
     */
    void setAddress( RakNet::SystemAddress addr );
    
    /**
     * get RakNet system address
     */
    RakNet::SystemAddress getAddress();

    /**
     * get custom char data of packet (without packet type)
     */
    const char * getData();
    
    /**
     * get custom char data length (without packet type)
     */
    const int getLength();
    
    /**
     * get char data of packet (packet type + custom data)
     */
    const char * getPacketData();
    
    /**
     * get length of packet data (packet type + custom data)
     */
    const int getPacketLength();
        
    /**
     * deallocates the Block including its data
     */
    void dealloc();
    
private:
    
    /**
     * private constructor
     * creating Blocks (similar as creating objects in Cocos2dx):
     * Block::create(...)
     */
    Block(const char * data, unsigned int length );
    
    /**
     * empty constructor
     */
    Block(){};
    
    /**
     * custom packet data (first byte is RakNet message type)
     */
    char * data;

    /**
     * length of the data (including first byte)
     */
    unsigned int length;

    /**
     * RakNet packet priority:
     *
     * PacketPriority::LOW_PRIORITY
     * PacketPriority::MEDIUM_PRIORITY
     * PacketPriority::HIGH_PRIORITY
     * PacketPriority::IMMEDIATE_PRIORITY
     */
    PacketPriority priority;
    
    /**
     * RakNet packet reliability:
     *
     * PacketReliability::RELIABLE
     * PacketReliability::RELIABLE_ORDERED
     * PacketReliability::RELIABLE_ORDERED_WITH_ACK_RECEIPT
     * PacketReliability::RELIABLE_SEQUENCED
     * PacketReliability::RELIABLE_WITH_ACK_RECEIPT
     * PacketReliability::UNRELIABLE
     * PacketReliability::UNRELIABLE_SEQUENCED
     * PacketReliability::UNRELIABLE_WITH_ACK_RECEIPT
     */
    PacketReliability reliability;
    
    /**
     * RakNet address, where the block will be sent
     */
    RakNet::SystemAddress address;

};

#endif // _BLOCK_H_