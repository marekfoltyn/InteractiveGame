//
//  BlockParser.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 24.01.16.
//
//

#include "Block.h"
#include "BlockParser.h"
#include "Definitions.h"

/**
 * Packet P_SERVER_NAME format:
 * 1                      ... packet type
 * sizeof(RakNet::TimeMS) ... timestamp
 *   (the rest of data)   ... server name
 */
std::string BlockParser::ServerName(Block * block)
{
    const char * data = (char *) block->getPacketData();
    int overhead = sizeof(unsigned char) + sizeof(RakNet::TimeMS);
    const char * name = (char *) data + overhead; // skip message type and response time
    
    //LOG("Parsing server name: %s\n", serverNameInPacket );
    return std::string( name );
}