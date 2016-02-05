//
//  ServerNameBlok.h
//  InteractiveController
//
//  Created by Marek Foltýn on 26.01.16.
//
//

#ifndef CollisionBlok_h
#define CollisionBlok_h

#include <string>
#include "Connector.h"

/**
 * Empty Blok signaling player's collision with whatever
 *
 * Type:
 * ==============================================
 * P_COLLISION
 *
 */
class CollisionBlok{
public:
    
    static Blok * create();
    
};


#endif /* CollisionBlok_h */
