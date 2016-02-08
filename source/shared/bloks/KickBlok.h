//
//  KickBlok.h
//  InteractiveController
//
//  Created by Marek Foltýn on 26.01.16.
//
//

#ifndef KickBlok_h
#define KickBlok_h

#include "Connector.h"

/**
 * Empty Blok signaling that player has kicked *
 * Type:
 * ==============================================
 * P_KICK
 *
 */
class KickBlok{
public:
    
    static Blok * create();
    
};


#endif /* KickBlok_h */
