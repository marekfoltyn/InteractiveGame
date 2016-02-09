//
//  AdminBlok.h
//  InteractiveController
//
//  Created by Marek Foltýn on 26.01.16.
//
//

#ifndef AdminBlok_h
#define AdminBlok_h

#include "Connector.h"

/**
 * Empty Blok signaling that player is Admin *
 * ==============================================
 * type: P_ADMIN
 *
 */
class AdminBlok{
public:
    
    static Blok * create();
    
};


#endif /* AdminBlok_h */
