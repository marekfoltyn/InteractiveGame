#ifndef  _PlayerCollisionHandler_H_
#define  _PlayerCollisionHandler_H_

#include "Game.h"
#include "AbstractHandlers.h"
#include "Player.h"

class PlayerCollisionHandler: public CollisionHandler{
public:
    
    PlayerCollisionHandler(Game *);
    
    void execute(cocos2d::PhysicsBody * first, cocos2d::PhysicsBody * second);
    
private:
    
    Game * game;
};

#endif // _PlayerCollisionHandler_H_