#ifndef  _Blok_H_
#define  _Blok_H_

#include "MessageIdentifiers.h"
#include "RakPeerInterface.h"

#include "string.h"


/**
 * Representation of game message to be sent to network.
 * Blok also includes information about packet - type, reliability, priority, ordering, address, ...
 * It is used as a wrapper for data to be sent to network and also for received data
 * Example:
 *
 * Blok * b;
 *
 * ... // init, fill with data, adress and so on...
 *
 * Connector::getInstance()->send(b);
 */
class Blok {
public:
    
    /**
     * create a Blok and copies data so the data has to be freed manually
     * @param byteSize size of the data
     */
    static Blok * create(const char * data, unsigned int len );
    
    /**
     * create a Blok from received packet
     * reliability and priority will be undefined
     */
    static Blok * create(RakNet::Packet * p);
    
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
     * set RakNet system address the Blok should be sent
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
     * send the packet to the address (and deallocates itself)
     */
    void send();
    
    /**
     * deallocates the Blok including its data
     */
    void deallocate();
    
private:
    
    /**
     * internal method
     * load raw data to memory
     */
    void loadData(const char * data, unsigned int length);
    
    /**
     * private constructor
     * creating Bloks (similar as creating objects in Cocos2dx):
     * Blok::create(...)
     */
    Blok(const char * data, unsigned int length );
    
    /**
     * private constructor
     * creating Bloks from received packet
     * Blok::create(...)
     */
    Blok( RakNet::Packet * packet );
    
    /**
     * empty constructor
     */
    Blok(){};
    
    /**
     * pointer to a RakNet packet (used if Blok was created from received packet)
     */
    RakNet::Packet * packet;
    
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
     *
     * More info in RakNet documentation
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
     
     * More info in RakNet documentation
     */
    PacketReliability reliability;
    
    /**
     * RakNet address, where the Blok will be sent
     */
    RakNet::SystemAddress address;
    
};

#endif // _Blok_H_