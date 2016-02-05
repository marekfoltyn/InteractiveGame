//
//  Blok.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 23.01.16.
//

#include "Blok.h"
#include "Connector.h"


Blok::Blok(const char * d, unsigned int len )
{
    
    length = len+1; // +1 ... message type byte
    data = new char[length];
    data[0] = 0; // unknown type yet
    
    if(d != nullptr && len > 0)
    {
        memcpy(data+1, d, len*sizeof(char));
    }
    
    // default values
    priority = PacketPriority::LOW_PRIORITY;
    reliability = PacketReliability::UNRELIABLE;
    address = RakNet::UNASSIGNED_SYSTEM_ADDRESS;
    packet=nullptr;
}

Blok::Blok(RakNet::Packet * packet)

// calling default constructor before
: Blok( (const char *) packet->data+1, packet->length-1) // skip first byte
{
    setAddress( packet->systemAddress );
    setType( packet->data[0] );
    this->packet = packet;
}


Blok * Blok::create(const char * data, unsigned int len )
{
    return new Blok(data, len);
}


Blok * Blok::create(RakNet::Packet * p)
{
    return new Blok(p);
}


void Blok::setType(unsigned char type)
{
    data[0] = type;
}


unsigned char Blok::getType()
{
    return data[0];
}


void Blok::setReliability( PacketReliability r )
{
    reliability = r;
}


PacketReliability Blok::getReliability()
{
    return reliability;
}


void Blok::setPriority( PacketPriority p )
{
    priority = p;
}


PacketPriority Blok::getPriority()
{
    return priority;
}


void Blok::setAddress( RakNet::SystemAddress addr )
{
    address = addr;
}


RakNet::SystemAddress Blok::getAddress()
{
    return address;
}


const char * Blok::getData()
{
    return data+1; // skip the packet type
}


const int Blok::getLength()
{
    return length-1; // skip the packet type
}


const char * Blok::getPacketData()
{
    return data;
}


const int Blok::getPacketLength()
{
    return length;
}


void Blok::deallocate()
{
    delete [] data;
    
    if(packet != nullptr)
    {
        Connector::getInstance()->getInterface()->DeallocatePacket(packet);
    }
}

