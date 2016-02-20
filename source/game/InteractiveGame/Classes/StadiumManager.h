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
#include "StadiumScene.h"


/**
 * class that manages stadium - constructs and modifies object in it
 * cooperating with the Scene and game logic (bonuses, pitch scaling, ...)
 */
class StadiumManager{
public:
    
    static StadiumManager * create(StadiumScene * scene);
    
    void setPitch();
    
private:
    
    StadiumManager(StadiumScene * scene);
    
    StadiumScene * scene;
    cocos2d::Director * director;
};

#endif /* StadiumManager_h */
