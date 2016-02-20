#include "NewPlayerHandler.h"
#include "Game.h"

void NewPlayerHandler::execute(GameNet::Box * box)
{
    CCLOG("New player: %s", box->getData().c_str() );
    game->getScene()->tempNewPlayer(box);
}