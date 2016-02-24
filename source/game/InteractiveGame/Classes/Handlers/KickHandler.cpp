#include "KickHandler.h"
#include "Game.h"
#include "GameplayDefinitions.h"

#include <string>

void KickHandler::execute(GameNet::Box * box)
{
    
    switch (box->getType()) {
        case P_KICK_PRESSED:
            pressed(box);
        break;
            
        case P_KICK_RELEASED:
            released(box);
        break;
            
        default:
        break;
    }
    
}


void KickHandler::pressed(GameNet::Box * box)
{
    int id = box->getId();
    unsigned int intensity = atoi( box->getData().c_str() );
    auto player = game->getPlayer(id);
    auto playerSprite = player->getSprite();
    
    playerSprite->schedule([player, intensity](float dt)
    {
        player->setSpeedScale( player->getSpeedScale() - 1/30.0 );
        CCLOG("spedScale: %f", player->getSpeedScale());
    }
    ,Definitions::TIME_KICK_FORCE_MAX/20, 20, 0, SCHEDULE_KICK_SLOWING);
}

void KickHandler::released(GameNet::Box * box)
{

    int id = box->getId();
    unsigned int intensity = atoi( box->getData().c_str() );
    
    auto player = game->getPlayer(id);
    auto playerSprite = player->getSprite();
    auto ball = game->getScene()->getChildByName<cocos2d::Sprite *>(NODE_BALL);
    
    float distance = ball->getPosition().distance( playerSprite->getPosition() );
    
    // reset speedScale
    playerSprite->unschedule(SCHEDULE_KICK_SLOWING);
    player->setSpeedScale(1);
    
    // pass ball
    if( distance < 2.0/3 * ((playerSprite->getContentSize().width * SCALE_BALL + ball->getContentSize().width * SCALE_BALL )) )
    {
        float force;
        
        if( box->getData().length() == 0 ){
            force = 0;
        } else {
            force = (intensity/255.0);
        }
        
        auto direction = ball->getPosition() - playerSprite->getPosition();
        direction.normalize();
        int kickForce = 200000 + 800000 * force;
        auto impulse = direction * kickForce;
        //impulse.negate();
        ball->getPhysicsBody()->applyImpulse( impulse );
        
        
        CCLOG("Ball pass. (force = %f%%)", force*100.0);
    }

    
}
