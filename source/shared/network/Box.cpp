//
//  Box.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 23.01.16.
//

#include "Box.h"
#include "Connector.h"

using namespace GameNet;

Box::Box(const char * d, unsigned int len )
{
    
    loadData(d, len);
    
    // default values
    priority = PacketPriority::HIGH_PRIORITY;
    reliability = PacketReliability::RELIABLE;
    address = Connector::getInstance()->getServer();
    packet=nullptr;
}

Box::Box(RakNet::Packet * packet)
{
    const char * data = (char *) packet->data + 1; // skip first byte
    unsigned int len = packet->length - 1;
    loadData(data, len);
    
    setAddress( packet->systemAddress );
    setType( packet->data[0] );
    this->packet = packet;
}


Box * Box::create(const char * data, unsigned int len )
{
    return new Box(data, len);
}


Box * Box::create(RakNet::Packet * p)
{
    return new Box(p);
}


void Box::setType(unsigned char type)
{
    data[0] = type;
}


unsigned char Box::getType()
{
    return data[0];
}


void Box::setReliability( PacketReliability r )
{
    reliability = r;
}


PacketReliability Box::getReliability()
{
    return reliability;
}


void Box::setPriority( PacketPriority p )
{
    priority = p;
}


PacketPriority Box::getPriority()
{
    return priority;
}


void Box::setAddress( RakNet::SystemAddress addr )
{
    address = addr;
}


RakNet::SystemAddress Box::getAddress()
{
    return address;
}


const char * Box::getData()
{
    return data+1; // skip the packet type
}


const int Box::getLength()
{
    return length-1; // skip the packet type
}


const char * Box::getPacketData()
{
    return data;
}


const int Box::getPacketLength()
{
    return length;
}

void Box::send()
{
    Connector::getInstance()->send(this);
    this->deallocate();
}

void Box::deallocate()
{
    delete [] data;
    
    if(packet != nullptr)
    {
        Connector::getInstance()->getInterface()->DeallocatePacket(packet);
    }
    
    delete this;
}



void Box::loadData(const char * d, unsigned int len)
{
    length = len+1; // +1 ... message type byte
    data = new char[length];
    data[0] = 0; // unknown type yet
    
    if(d != nullptr && len > 0)
    {
        memcpy(data+1, d, len*sizeof(char));
    }
}
