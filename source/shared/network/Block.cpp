//
//  Block.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 23.01.16.
//

#include "MessageIdentifiers.h"
#include "RakPeerInterface.h"
#include "Connector.h"
#include "Block.h"
#include "string.h"

Block::Block(const char * d, unsigned int len )
{
    //TODO: vyresit konstruktory (neduplikovat kod)
    
    length = len+1;
    data = new char[length];
    memcpy(data+1, d, len*sizeof(char));
    data[0] = d[0];
    
    // default values
    priority = PacketPriority::LOW_PRIORITY;
    reliability = PacketReliability::UNRELIABLE;
    address = RakNet::UNASSIGNED_SYSTEM_ADDRESS;
    packet=nullptr;
}

Block::Block(RakNet::Packet * packet)

// calling no-packet constructor
: Block( (const char *) packet->data+1, packet->length-1) // skip first byte
{
    setAddress( packet->systemAddress );
    setType( packet->data[0] );
    this->packet = packet;
}


Block * Block::create(const char * data, unsigned int len )
{
    return new Block(data, len);
}


Block * Block::create(RakNet::Packet * p)
{
    return new Block(p);
}


void Block::setType(unsigned char type)
{
    data[0] = type;
}


unsigned char Block::getType()
{
    return data[0];
}


void Block::setReliability( PacketReliability r )
{
    reliability = r;
}


PacketReliability Block::getReliability()
{
    return reliability;
}


void Block::setPriority( PacketPriority p )
{
    priority = p;
}


PacketPriority Block::getPriority()
{
    return priority;
}


void Block::setAddress( RakNet::SystemAddress addr )
{
    address = addr;
}


RakNet::SystemAddress Block::getAddress()
{
    return address;
}


const char * Block::getData()
{
    return data+1; // skip the packet type
}


const int Block::getLength()
{
    return length-1; // skip the packet type
}


const char * Block::getPacketData()
{
    return data;
}


const int Block::getPacketLength()
{
    return length;
}


void Block::deallocate()
{
    if(packet == nullptr)
    {
        delete [] data;
    }
    else
    {
        Connector::getInstance()->getInterface()->DeallocatePacket(packet);
    }
}

