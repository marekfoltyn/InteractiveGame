#include "KickHandler.h"
#include "Game.h"
#include "GameDefinitions.h"

void KickHandler::execute(GameNet::Box * box)
{
    CCLOG("Tackle.");
    
    int id = box->getId();
    
    auto player = game->getPlayer(id)->getSprite();
    auto ball = game->getScene()->getChildByName<cocos2d::Sprite *>(NODE_BALL);
    
    float distance = ball->getPosition().distance( player->getPosition() );
    
    // pass ball
    if( distance < 2.0/3 * ((player->getContentSize().width * SCALE_BALL + ball->getContentSize().width * SCALE_BALL )) )
    {
        auto direction = ball->getPosition() - player->getPosition();
        direction.normalize();
        int kickForce = 600000;
        auto impulse = direction * kickForce;
        //impulse.negate();
        
        ball->getPhysicsBody()->applyImpulse( impulse );
        CCLOG("Ball pass.");
    }
}