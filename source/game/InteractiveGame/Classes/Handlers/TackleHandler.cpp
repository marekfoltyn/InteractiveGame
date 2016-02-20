#include "TackleHandler.h"
#include "Game.h"

void TackleHandler::execute(GameNet::Box * box)
{
    CCLOG("New player: %s", box->getData().c_str() );
    game->getScene()->tempTackle(box);
}