//
//  StadiumManager
//  InteractiveGame
//
//  Created by Marek Foltýn on 05.02.16.
//
//

#ifndef StadiumManager_h
#define StadiumManager_h

#include "cocos2d.h"
#include "Connector.h"


/**
 * class that manages stadium - constructs and modifies object in it
 * cooperating with the Scene and game logic (bonuses, pitch scaling, ...)
 */
class StadiumManager{
public:
    
    static StadiumManager * create(cocos2d::Scene * scene);
    
    void setPitch();
    
private:
    
    StadiumManager(cocos2d::Scene * scene);
    
    cocos2d::Scene * scene;
    
};

#endif /* StadiumManager_h */
