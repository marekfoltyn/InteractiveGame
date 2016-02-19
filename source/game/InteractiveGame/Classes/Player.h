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
    cocos2d::Sprite * getSprite(){ return sprite; }
    
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
    cocos2d::Vec2 getPreviousForce(){ return previousForce; }
    
    /**
     * set applied force in this accelerometer blok
     */
    void setAppliedForce(cocos2d::Vec2 force);
    
    /**
     * set this player as admin
     */
    void setAsAdmin();
    
    /**
     * returns true, if the player is admin
     */
    bool isAdmin(){ return admin; }
    
private:
    
    /**
     * cocos2dx sprite
     */
    cocos2d::Sprite * sprite;
    
    /**
     * RakNet address
     */
    RakNet::SystemAddress address;
    
    /**
     * force applied in previously received AccelerationBlok
     * necessary for player's direction change
     */
    cocos2d::Vec2 previousForce;
    
    /**
     * indicates if the players is admin
     * (can control the stadium)
     */
    bool admin;
    
    /**
     * private constructor - use Player::create()
     */
    Player(RakNet::SystemAddress address);
};

#endif /* Player_h */
