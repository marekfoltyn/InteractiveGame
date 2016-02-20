#include "DisconnectHandler.h"
#include "Game.h"

void DisconnectHandler::execute(GameNet::Box * box)
{
    CCLOG("New player: %s", box->getData().c_str() );
    game->getScene()->tempDisconnect(box);
}