#include "DisconnectHandler.h"
#include "Game.h"

bool DisconnectHandler::execute(GameNet::Box * box)
{
    CCLOG("%s disconnected.", box->getAddress().ToString());
    
    int id = box->getId();
    auto player = game->getPlayer(id);
    if(player == nullptr){
        CCLOG("Player not found in the Game.");
        return false;
    }
    
    game->getStadiumManager()->removePlayer(player);
    game->removePlayer(player);
    
    // set new admin
    if( player->isAdmin() && game->playersCount() >= 1 )
    {
        auto newAdmin = game->getRandomPlayer();
        newAdmin->setAsAdmin();
        game->getStadiumManager()->setAdminName( newAdmin->getName() );
        CCLOG("New admin is %s", newAdmin->getName().c_str());
    }
    else if (game->playersCount() == 0)
    {
        game->getStadiumManager()->setAdminName("");
    }
    
    player->destroy();
    return false;
}