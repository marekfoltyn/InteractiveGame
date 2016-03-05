#include "ResetHandler.h"
#include "Game.h"

bool ResetHandler::execute(GameNet::Box * box)
{
    game->getStadiumManager()->resetScore();
    return false;
}
