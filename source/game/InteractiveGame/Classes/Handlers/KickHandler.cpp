#include "KickHandler.h"
#include "Game.h"
#include "GameplayDefinitions.h"

#include <string>

bool KickHandler::execute(GameNet::Box * box)
{
    int id = box->getId();
    unsigned int intensity = atoi( box->getData().c_str() );
    
    auto player = game->getPlayer(id);
    auto playerSprite = player->getSprite();
    auto ball = game->getStadium()->getChildByName<cocos2d::Sprite *>(NODE_BALL);
    
    if(ball == nullptr)
    {
        CCLOG("No ball in the game...");
        return false;
    }
    
    if( ball->getPhysicsBody()->getTag() == StadiumScene::BALL_NON_KICKABLE)
    {
        CCLOG("Ball is non kickable.");
        return false;
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
    
    return false;
}
