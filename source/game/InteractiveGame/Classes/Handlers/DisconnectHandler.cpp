#include "DisconnectHandler.h"
#include "Game.h"

void DisconnectHandler::execute(GameNet::Box * box)
{
    CCLOG("%s disconnected.", box->getAddress().ToString());
    
    int id = box->getId();
    auto player = game->getPlayer(id);
    
    game->getStadiumManager()->removePlayer(player);
    game->removePlayer(player);
    
    // set new admin
    if( player->isAdmin() && game->playersCount() >= 1 )
    {
        auto newAdmin = game->getRandomPlayer();
        newAdmin->setAsAdmin();
        CCLOG("New admin is %s", newAdmin->getName().c_str());
    }
    
    player->destroy();
}