#ifndef  _Handler_H_
#define  _Handler_H_

#include "cocos2d.h"

class CollisionHandler{
public:
    
    virtual void execute(cocos2d::PhysicsBody * first, cocos2d::PhysicsBody * second) = 0;
    
};

#endif // _Handler_H_