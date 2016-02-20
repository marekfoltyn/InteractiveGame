#include "KickHandler.h"
#include "Game.h"

void KickHandler::execute(GameNet::Box * box)
{
    CCLOG("New player: %s", box->getData().c_str() );
    game->getScene()->tempKick(box);
}