//
//  BlockParser.h
//  InteractiveController
//
//  Created by Marek Foltýn on 24.01.16.
//
//

#include "Block.h"
#include <string>


#ifndef BlockParser_h
#define BlockParser_h

/**
 * class for parsing Block data to data structures dependent of Block (packet) type
 */
class BlockParser{
public:
    /**
     * parse packet P_SERVER_NAME
     * returns string with the server name
     */
    static std::string ServerName( Block * block );
    
    
    
};

#endif /* BlockParser_h */
