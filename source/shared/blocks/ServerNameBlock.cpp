//
//  ServerNameBlock.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 26.01.16.
//
//

#include "ServerNameBlock.h"



std::string ServerNameBlock::ServerName(Block * block)
{
    return std::string( block->getData()+sizeof(RakNet::TimeMS) ); // skip ping timestamp
}