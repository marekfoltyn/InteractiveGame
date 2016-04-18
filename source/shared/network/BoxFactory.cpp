#include "Connector.h"
#include "BoxFactory.h"

#include "AccelerationMessage.h"

#include <string>

using namespace GameNet;

Box * BoxFactory::acceleration(double x, double y, double z)
{
    auto msg = AccelerationMessage(x,y,z);
    auto box = Box::create( msg.serialize() );
    box->setType(BOX_ACCELERATION);
    box->setPriority(PacketPriority::IMMEDIATE_PRIORITY);
    box->setReliability(PacketReliability::UNRELIABLE);

    return box;
}

Box * BoxFactory::admin(RakNet::SystemAddress address, GameState gameState)
{
    std::string message;
    gameState.SerializeToString( &message );
    
    Box * box = Box::create(message);
    box->setType(BOX_ADMIN);
    box->setReliability(PacketReliability::RELIABLE_ORDERED);
    box->setPriority(PacketPriority::LOW_PRIORITY);
    box->setAddress(address);
    return box;
}

Box * BoxFactory::collision(RakNet::SystemAddress address)
{
    Box * box = Box::createEmpty();
    box->setType(BOX_COLLISION);
    box->setReliability(PacketReliability::RELIABLE);
    box->setPriority(PacketPriority::IMMEDIATE_PRIORITY);
    box->setAddress(address);    
    return box;
}

Box * BoxFactory::resetScore()
{
    Box * box = Box::createEmpty();
    box->setType(BOX_RESET_SCORE);
    box->setReliability(PacketReliability::RELIABLE);
    box->setPriority(PacketPriority::LOW_PRIORITY);
    return box;
}

Box * BoxFactory::kick(unsigned int intensity)
{
    // normalize intensity (0-255)
    if( intensity > 255) intensity = 255;
    std::stringstream ss;
    ss << intensity;
    Box * box = Box::create( ss.str() );
    box->setType(BOX_KICK);
    box->setReliability(PacketReliability::RELIABLE);
    box->setPriority(PacketPriority::IMMEDIATE_PRIORITY);
    return box;
}


Box * BoxFactory::playerName(std::string name)
{
    Box * box = Box::create(name);
    box->setType(BOX_PLAYER_NAME);
    box->setReliability(PacketReliability::RELIABLE);
    box->setPriority(PacketPriority::LOW_PRIORITY);
    return box;
}


Box * BoxFactory::teamSelection(std::string team)
{
    Box * box = Box::create(team);
    box->setType(BOX_TEAM_SELECT);
    box->setReliability(PacketReliability::RELIABLE);
    box->setPriority(PacketPriority::LOW_PRIORITY);
    return box;
}


Box * BoxFactory::gameStream(RakNet::SystemAddress player, PBGameStream & stream)
{
    Box * box;
    std::string serialized;

    stream.SerializeToString(&serialized);
    box = Box::create(serialized);
    box->setType(BOX_GAME_STREAM);
    box->setAddress(player);
    box->setReliability(PacketReliability::UNRELIABLE_SEQUENCED);
    box->setPriority(PacketPriority::IMMEDIATE_PRIORITY);
    return box;
}


Box * BoxFactory::gameStreamReliable(RakNet::SystemAddress player, PBGameStream & stream)
{
    Box * box = gameStream(player, stream);
    box->setReliability(PacketReliability::RELIABLE_ORDERED);
    return box;
}


