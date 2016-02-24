#include "Definitions.h"
#include "BoxFactory.h"

#include "AccelerationMessage.h"

#include <string>

using namespace GameNet;

Box * BoxFactory::acceleration(double x, double y, double z)
{
    auto msg = AccelerationMessage(x,y,z);
    auto box = Box::create( msg.serialize() );
    box->setType(P_ACCELERATION);
    box->setPriority(PacketPriority::IMMEDIATE_PRIORITY);
    box->setReliability(PacketReliability::UNRELIABLE);

    return box;
}

Box * BoxFactory::admin(RakNet::SystemAddress address)
{
    Box * box = Box::createEmpty();
    box->setType(P_ADMIN);
    box->setReliability(PacketReliability::RELIABLE);
    box->setPriority(PacketPriority::LOW_PRIORITY);
    box->setAddress(address);
    return box;
}

Box * BoxFactory::collision(RakNet::SystemAddress address)
{
    Box * box = Box::createEmpty();
    box->setType(P_COLLISION);
    box->setReliability(PacketReliability::RELIABLE);
    box->setPriority(PacketPriority::IMMEDIATE_PRIORITY);
    box->setAddress(address);    
    return box;
}

Box * BoxFactory::resetScore()
{
    Box * box = Box::createEmpty();
    box->setType(P_RESET_SCORE);
    box->setReliability(PacketReliability::RELIABLE);
    box->setPriority(PacketPriority::LOW_PRIORITY);
    return box;
}

Box * BoxFactory::kickPressed()
{
    Box * box = Box::createEmpty();
    box->setType(P_KICK_PRESSED);
    box->setReliability(PacketReliability::RELIABLE);
    box->setPriority(PacketPriority::IMMEDIATE_PRIORITY);
    return box;
}

Box * BoxFactory::kickReleased(unsigned int intensity)
{
    if( intensity > 255) intensity = 255;
    std::stringstream ss;
    ss << intensity;
    Box * box = Box::create( ss.str() );
    box->setType(P_KICK_RELEASED);
    box->setReliability(PacketReliability::RELIABLE);
    box->setPriority(PacketPriority::IMMEDIATE_PRIORITY);
    return box;
}


Box * BoxFactory::playerName(std::string name)
{
    Box * box = Box::create(name);
    box->setType(P_PLAYER_NAME);
    box->setReliability(PacketReliability::RELIABLE);
    box->setPriority(PacketPriority::LOW_PRIORITY);
    return box;
}