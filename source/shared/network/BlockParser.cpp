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

std::string BlockParser::ServerName(Block * block)
{
    const char * name = block->getData();
    LOG("Parsing server name: %c", name[5] );
    return (char *) name;
}