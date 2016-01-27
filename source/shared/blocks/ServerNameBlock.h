//
//  ServerNameBlock.h
//  InteractiveController
//
//  Created by Marek Foltýn on 26.01.16.
//
//

#ifndef ServerNameBlock_h
#define ServerNameBlock_h

#include <string>
#include "Connector.h"

/**
 * Block with the server name (used when phone is not connected)
 * Server creates this packet automatically, so we don't have to
 * implement ServerNameBlock::create()
 *
 * Type:
 * ==============================================
 * P_SERVER_NAME
 *
 * Format:
 * ==============================================
 * server name (const char *)
 */
class ServerNameBlock{
public:
    
    /**
     * parse the server name
     */
    static std::string ServerName(Block * block);

};


#endif /* ServerNameBlock_h */
