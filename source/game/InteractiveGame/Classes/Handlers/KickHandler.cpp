#include "KickHandler.h"
#include "Game.h"
#include "GameDefinitions.h"

#include <string>

void KickHandler::execute(GameNet::Box * box)
{
    int id = box->getId();
    unsigned int data = atoi( box->getData().c_str() );
    
    auto player = game->getPlayer(id)->getSprite();
    auto ball = game->getScene()->getChildByName<cocos2d::Sprite *>(NODE_BALL);
    
    float distance = ball->getPosition().distance( player->getPosition() );
    
    // pass ball
    if( distance < 2.0/3 * ((player->getContentSize().width * SCALE_BALL + ball->getContentSize().width * SCALE_BALL )) )
    {
        float force;
        
        if( box->getData().length() == 0 ){
            force = 0;
        } else {
            force = (data/255.0);
        }

        auto direction = ball->getPosition() - player->getPosition();
        direction.normalize();
        int kickForce = 200000 + 800000 * force;
        auto impulse = direction * kickForce;
        //impulse.negate();
        ball->getPhysicsBody()->applyImpulse( impulse );
        
        
        CCLOG("Ball pass. (force = %f%%)", force*100.0);
    }
}