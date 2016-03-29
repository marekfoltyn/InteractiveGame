#include "cocos2d.h"
#include "AccelerationBoxHandler.h"
#include "Game.h"
#include "StadiumScene.h"
#include "AccelerationMessage.h"

bool AccelerationBoxHandler::execute(GameNet::Box * box)
{
    
    int id = box->getId();
    auto msg = GameNet::AccelerationMessage();
    bool res = msg.deserialize(box->getData());
    if(res == false)
    {
        CCLOG("AccelerationMessage deserialization failed.");
        return false;
    }
    
    float x = (float) msg.getX();
    float y = (float) msg.getY();
    float forceSize = sqrtf( x*x + y*y );
    
    // coord clean
    if( fabs(x) < 0.08 ) x = 0;
    if( fabs(y) < 0.08 ) y = 0;
    
    auto player = game->getPlayer(id);
    if(player == nullptr)
    {
        CCLOG("Player not found in Game::players.");
        return false;
    }
    auto sprite = player->getSprite();
    
    cocos2d::Vec2 force = cocos2d::Vec2(1000000000*x*(player->getSpeedMultiplier()), 1000000000*y*(player->getSpeedMultiplier()));
    cocos2d::Vec2 prevForce = player->getPreviousForce();
    cocos2d::Vec2 oppositePrevForce = cocos2d::Vec2( - prevForce.x, - prevForce.y );
    player->setAppliedForce(force);
    
    sprite->getPhysicsBody()->applyForce(force);
    sprite->getPhysicsBody()->applyForce(oppositePrevForce);
    sprite->getPhysicsBody()->setVelocityLimit(450*forceSize*(player->getSpeedScale())*(player->getSpeedMultiplier()));
    
    return false;
}