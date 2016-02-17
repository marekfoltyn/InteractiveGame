//
//  ServerNameBox.h
//  InteractiveController
//
//  Created by Marek Foltýn on 26.01.16.
//
//

#ifndef CollisionBox_h
#define CollisionBox_h

#include <string>
#include "Connector.h"

using namespace GameNet;

/**
 * Empty Box signaling player's collision with whatever
 *
 * Type:
 * ==============================================
 * P_COLLISION
 *
 */
class CollisionBox{
public:
    
    static Box * create();
    
};


#endif /* CollisionBox_h */
