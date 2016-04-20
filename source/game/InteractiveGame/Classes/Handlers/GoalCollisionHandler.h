#ifndef  _GoalCollisionHandler_H_
#define  _GoalCollisionHandler_H_

#include "Game.h"
#include "AbstractHandlers.h"
#include "Player.h"

class GoalCollisionHandler: public CollisionHandler{
public:
    
    GoalCollisionHandler(Game *, cocos2d::Director *);
    
    void execute(cocos2d::PhysicsBody * first, cocos2d::PhysicsBody * second);
    
private:
    
    cocos2d::Director * director;
    Game * game;
    
    cocos2d::PhysicsBody * goal;
    cocos2d::PhysicsBody * ball;
    
    /**
     * show score animations and reset ball position
     * side: Definitions::LEFT or Definitions::RIGHT
     */
    void scoreSequence(int side);
};

#endif // _GoalCollisionHandler_H_