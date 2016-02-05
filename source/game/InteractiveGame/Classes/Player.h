//
//  Player.hpp
//  InteractiveGame
//
//  Created by Marek Foltýn on 05.02.16.
//
//

#ifndef Player_h
#define Player_h

#include "cocos2d.h"
#include "Connector.h"

USING_NS_CC;

/**
 * Class representing a human player
 * includes all information needed for drawing, game logic and networking
 */
class Player{
public:
    
    /**
     * create a new Player instance (after connecting)
     */
    static Player * create(RakNet::SystemAddress address);
    
    /**
     * get the cocos2dx Sprite object
     */
    Sprite * getSprite(){ return sprite; }
    
    /**
     * get the network address
     */
    RakNet::SystemAddress getAddress(){ return address; }
    
    /**
     * deallocate the instance (after disconnection)
     */
    void destroy();
    
    /**
     * get applied force in previous accelerometer blok
     */
    Vec2 getPreviousForce(){ return previousForce; }
    
    /**
     * set applied force in this accelerometer blok
     */
    void setAppliedForce(Vec2 force);
    
private:
    
    Sprite * sprite;
    RakNet::SystemAddress address;
        Vec2 previousForce;
    
    /**
     * private constructor - use Player::create()
     */
    Player(RakNet::SystemAddress address);
};

#endif /* Player_h */
