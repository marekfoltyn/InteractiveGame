#include "PlayerCollisionHandler.h"
#include "Connector.h"
#include "BoxFactory.h"

void PlayerCollisionHandler::execute(cocos2d::PhysicsBody * first, cocos2d::PhysicsBody * second)
{
    int id = first->getTag();
    auto player = game->getPlayer(id);
    
    CCLOG("Player %s collided (handler)", player->getAddress().ToString() );
    GameNet::BoxFactory::collision(player->getAddress())->send();
}