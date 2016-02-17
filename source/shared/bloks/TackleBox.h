//
//  TackleBox.h
//  InteractiveController
//
//  Created by Marek Foltýn on 26.01.16.
//
//

#ifndef TackleBox_h
#define TackleBox_h

#include "Connector.h"

using namespace GameNet;

/**
 * Empty Box signaling that player has Tackled *
 * Type:
 * ==============================================
 * P_Tackle
 *
 */
class TackleBox{
public:
    
    static Box * create();
    
};


#endif /* TackleBox_h */
