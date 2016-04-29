//
//  Player.hpp
//  InteractiveGame
//
//  Created by Marek Foltýn on 05.02.16.
//
//

#ifndef Player_h
#define Player_h

#include <string>

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
    static Player * create(RakNet::SystemAddress address, std::string name);

    /**
     * create a new Player instance (without address - client)
     */
    static Player * create(std::string name);
    
    
    /**
     * get the cocos2dx Sprite object
     */
    cocos2d::Sprite * getSprite(){ return sprite; }
    
    /**
     * get the network address
     */
    RakNet::SystemAddress getAddress(){ return address; }
    
    /**
     * get the player's name
     */
    std::string getName(){ return name; }
    
    /**
     * team manipulation
     */
    std::string getTeam(){return team;}
    void setTeam(std::string newTeam);
    
    /**
     * get the player's id based on the SystemAddress hash
     */
    int getId();
    
    /**
     * deallocate the instance (after disconnection)
     */
    void destroy();
    
    /**
     * get applied force in previous accelerometer blok
     */
    cocos2d::Vec2 getPreviousForceVector(){ return appliedForceVector; }
    
    /**
     * set applied force in this accelerometer blok
     */
    void applyForce(cocos2d::Vec2 force);
    
    /**
     * set this player as admin
     */
    void setAsAdmin();
    
    /**
     * returns true, if the player is admin
     */
    bool isAdmin(){ return admin; }
    
    /**
     * speedScale getter / setter
     */
    void setSpeedScale(float scale);
    float getSpeedScale(){ return speedScale; }
    
    /**
     * kickMultiplier getter / setter
     */
    void setKickMultiplier(float multiplier);
    void addKickMultiplier(float dt);
    float getKickMultiplier(){ return kickMultiplier; }

    /**
     * speedMultiplier getter / setter
     */
    void setSpeedMultiplier(float multiplier);
    void addSpeedMultiplier(float dt);
    float getSpeedMultiplier(){ return speedMultiplier; }
    
    /**
     * blink with eyes :)
     */
    void blink();
    
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
     * player's name
     */
    std::string name;
    
    /**
     * player's team color
     */
    std::string team;
    
    /**
     * force applied in previously received AccelerationBlok
     * necessary for player's direction change
     */
    cocos2d::Vec2 appliedForceVector;
    cocos2d::Vec2 realPreviousForce;
    
    /**
     * indicates if the players is admin
     * (can control the stadium)
     */
    bool admin;
    
    /**
     * interval [0,1] for maximum velocity scaling (kick loading)
     */
    float speedScale;
    
    /**
     * bonus kick scale factor (normal is 1) - multiplies kick force
     */
    float kickMultiplier;

    /**
     * bonus speed scale factor (normal is 1) - multiplies velocity
     */
    float speedMultiplier;
    
    /**
     * private constructor - use Player::create()
     */
    Player(RakNet::SystemAddress address, std::string name);

    void autoBlink();
};

#endif /* Player_h */
