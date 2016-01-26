//
//  BlockManager.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 24.01.16.
//
//

#include "Block.h"
#include "BlockManager.h"
#include "Definitions.h"

/**
 * Packet P_SERVER_NAME format:
 * 1                      ... packet type
 * sizeof(RakNet::TimeMS) ... timestamp
 *   (the rest of data)   ... server name
 */
std::string BlockManager::parseServerName(Block * block)
{
    const char * data = (char *) block->getPacketData();
    int overhead = sizeof(unsigned char) + sizeof(RakNet::TimeMS);
    const char * name = (char *) data + overhead; // skip message type and response time
    
    //LOG("Parsing server name: %s\n", serverNameInPacket );
    return std::string( name );
}


Block * BlockManager::createAcceleration( cocos2d::Acceleration * acc)
{
    BlockManager::Acceleration a;
    a.x = acc->x;
    a.y = acc->y;
    a.z = acc->z;
    
    Block * block = Block::create( (const char *) &a, sizeof(BlockManager::Acceleration));
    block->setType(P_ACCELERATION);
    block->setReliability(PacketReliability::UNRELIABLE);
    block->setPriority(PacketPriority::HIGH_PRIORITY);
    return block;
}