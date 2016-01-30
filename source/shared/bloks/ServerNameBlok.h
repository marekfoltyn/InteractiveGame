//
//  ServerNameBlok.h
//  InteractiveController
//
//  Created by Marek Foltýn on 26.01.16.
//
//

#ifndef ServerNameBlok_h
#define ServerNameBlok_h

#include <string>
#include "Connector.h"

/**
 * Blok with the server name (used when phone is not connected)
 * Server creates this packet automatically, so we don't have to
 * implement ServerNameBlok::create()
 *
 * Type:
 * ==============================================
 * P_SERVER_NAME
 *
 * Format:
 * ==============================================
 * server name (const char *)
 */
class ServerNameBlok{
public:
    
    /**
     * parse the server name
     */
    static std::string ServerName(Blok * blok);

};


#endif /* ServerNameBlock_h */
