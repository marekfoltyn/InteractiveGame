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
#include "VoidHandler.h"
#include "Player.h"


/**
 * class that manages stadium - constructs and modifies object in it
 * cooperating with the Scene and game logic (bonuses, pitch scaling, ...)
 */
class StadiumManager{
public:
    
    static StadiumManager * create();
    
    void drawPitch();
    
    void addExitButton( VoidHandler * handler );
    
    void addPlayer(Player * player);
    
    void removePlayer(Player * player);
    
    void resetScore();
    
    void runStadium();
    
    void addCollisionHandler(int bitmask, CollisionHandler * handler);
    
private:
    
    StadiumManager();
    
    StadiumScene * scene;
    cocos2d::Director * director;

    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    
};

#endif /* StadiumManager_h */
