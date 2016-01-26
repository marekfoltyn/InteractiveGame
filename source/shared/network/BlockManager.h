//
//  BlockParser.h
//  InteractiveController
//
//  Created by Marek Foltýn on 24.01.16.
//
//

#include "cocos2d.h"
#include "Block.h"
#include <string>


#ifndef BlockManager_h
#define BlockManager_h

/**
 * class for parsing Block data to data structures dependent of Block (packet) type
 */
class BlockManager{
public:
    /**
     * parse packet P_SERVER_NAME
     * returns string with the server name
     */
    static std::string parseServerName( Block * block );
    
    struct Acceleration{
        float x;
        float y;
        float z;
    };
    
    /**
     * create packet with acceleration information
     */
    static Block * createAcceleration( cocos2d::Acceleration * acc);
    
};

#endif /* BlockManager_h */
