//
//  Box.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 23.01.16.
//

#include "Box.h"
#include "Connector.h"

using namespace GameNet;

Box::Box(std::string data)
{
    connector = Connector::getInstance();
    
    loadData(data.c_str(), static_cast<unsigned int>( data.length() ) );
    
    // default values
    priority = PacketPriority::HIGH_PRIORITY;
    reliability = PacketReliability::RELIABLE;
    address = Connector::getInstance()->getServer();
    packet=nullptr;
}

Box::Box(RakNet::Packet * packet)
{
    connector = Connector::getInstance();
    
    const char * data = (char *) packet->data + 1; // skip first byte
    unsigned int len = packet->length - 1; // skip first byte
    loadData(data, len);
    
    setAddress( packet->systemAddress );
    setType( packet->data[0] );
    this->packet = packet;
}


Box * Box::create(std::string data)
{
    return new Box(data);
}

Box * Box::createEmpty()
{
    return new Box("");
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

int Box::getId()
{
    return (unsigned int) RakNet::SystemAddress::ToInteger(address);
}

std::string Box::getData()
{
    // return data+1 not working
    // implicit cast to std:string works
    // but the data are terminated after first null byte
    // e.g.: timestamp has four bytes, but usually the first three bytes
    // are null, so it would return an empty string
    // so the best option is to create std:string with specified length:
    return std::string(data+1, getLength()); // skip the packet type
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
    connector->send(this);
    this->deallocate();
}



void Box::deallocate()
{
    delete [] data;
    
    if(packet != nullptr)
    {
        connector->getInterface()->DeallocatePacket(packet);
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
