//
//  ResetScoreBlok.h
//  InteractiveController
//
//  Created by Marek Foltýn on 26.01.16.
//
//

#ifndef ResetScoreBlok_h
#define ResetScoreBlok_h

#include "Connector.h"

/**
 * Empty Blok signaling that player is ResetScore *
 * ==============================================
 * type: P_RESET_SCORE
 *
 */
class ResetScoreBlok{
public:
    
    static Blok * create();
    
};


#endif /* ResetScoreBlok_h */
