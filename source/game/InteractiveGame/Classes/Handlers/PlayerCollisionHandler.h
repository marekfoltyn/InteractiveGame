#ifndef  _PlayerCollisionHandler_H_
#define  _PlayerCollisionHandler_H_

#include "Game.h"
#include "CollisionHandler.h"
#include "Player.h"

class PlayerCollisionHandler: public CollisionHandler{
public:
    
    PlayerCollisionHandler(Game * game)
    {
        this->game = game;
    }
    
    void execute(cocos2d::PhysicsBody * first, cocos2d::PhysicsBody * second);
    
private:
    
    Game * game;
};

#endif // _PlayerCollisionHandler_H_