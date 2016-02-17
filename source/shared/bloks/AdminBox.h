//
//  AdminBox.h
//  InteractiveController
//
//  Created by Marek Foltýn on 26.01.16.
//
//

#ifndef AdminBox_h
#define AdminBox_h

#include "Connector.h"

using namespace GameNet;

/**
 * Empty Box signaling that player is Admin *
 * ==============================================
 * type: P_ADMIN
 *
 */
class AdminBox{
public:
    
    static Box * create();
    
};


#endif /* AdminBox_h */
