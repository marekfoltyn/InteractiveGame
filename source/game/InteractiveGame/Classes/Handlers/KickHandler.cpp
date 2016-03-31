#include "KickHandler.h"
#include "Game.h"
#include "GameplayDefinitions.h"

#include <string>

bool KickHandler::execute(GameNet::Box * box)
{
    
    switch (box->getType()) {
        case BOX_KICK_PRESSED:
            pressed(box);
        break;
            
        case BOX_KICK_RELEASED:
            released(box);
        break;
            
        default:
        break;
    }
    return false;
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
    auto ball = game->getStadium()->getChildByName<cocos2d::Sprite *>(NODE_BALL);
    
    // reset speedScale
    playerSprite->unschedule(SCHEDULE_KICK_SLOWING);
    player->setSpeedScale(1);
    
    if(ball == nullptr)
    {
        CCLOG("No ball in the game...");
        return;
    }
    
    if( ball->getPhysicsBody()->getTag() == StadiumScene::BALL_NON_KICKABLE)
    {
        CCLOG("Ball is non kickable.");
        return;
    }
    
    float distance = ball->getPosition().distance( playerSprite->getPosition() );
    
    // pass ball
    if( distance < 2.0/3 * ((playerSprite->getContentSize().width * SCALE_BALL + ball->getContentSize().width * SCALE_BALL )) )
    {
        float force;
        
        // when I take multiple kick bonuses, shoot would kick the ball
        // out of the stadium - let's allow maximum multiplier 2.0
        float realKickMultiplier = player->getKickMultiplier() > 2.0 ? 2.0 : player->getKickMultiplier();
        
        if( box->getData().length() == 0 ){
            force = 0;
        } else {
            force = (intensity/255.0);
        }
        
        auto direction = ball->getPosition() - playerSprite->getPosition();
        direction.normalize();
        int kickForce = 250000 + 750000 * force * realKickMultiplier;
        auto impulse = direction * kickForce;
        //impulse.negate();
        ball->getPhysicsBody()->applyImpulse( impulse );
        
        
        CCLOG("Ball pass. (force = %f%%)", force*100.0);
    }

    
}
