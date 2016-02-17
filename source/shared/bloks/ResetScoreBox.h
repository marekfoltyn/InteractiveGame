//
//  ResetScoreBox.h
//  InteractiveController
//
//  Created by Marek Foltýn on 26.01.16.
//
//

#ifndef ResetScoreBox_h
#define ResetScoreBox_h

#include "Connector.h"

using namespace GameNet;

/**
 * Empty Box signaling that player is ResetScore *
 * ==============================================
 * type: P_RESET_SCORE
 *
 */
class ResetScoreBox{
public:
    
    static Box * create();
    
};


#endif /* ResetScoreBox_h */
