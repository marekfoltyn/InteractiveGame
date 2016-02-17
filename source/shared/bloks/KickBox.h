//
//  KickBox.h
//  InteractiveController
//
//  Created by Marek Foltýn on 26.01.16.
//
//

#ifndef KickBox_h
#define KickBox_h

#include "Connector.h"

using namespace GameNet;

/**
 * Empty Box signaling that player has kicked the ball
 * Type:
 * ==============================================
 * P_KICK
 *
 */
class KickBox{
public:
    
    static Box * create();
    
};


#endif /* KickBox_h */
