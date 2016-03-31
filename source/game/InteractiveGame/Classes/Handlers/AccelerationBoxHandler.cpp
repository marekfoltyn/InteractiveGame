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
    Vec2 forceVector = Vec2(x, y);
    
    // coord clean
    if( fabs(x) < 0.08 ) x = 0;
    if( fabs(y) < 0.08 ) y = 0;
    
    auto player = game->getPlayer(id);
    if(player == nullptr)
    {
        CCLOG("Player not found in Game::players.");
        return false;
    }
    
    player->applyForce(forceVector);
    
    return false;
}