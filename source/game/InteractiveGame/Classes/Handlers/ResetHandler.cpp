#include "ResetHandler.h"
#include "Game.h"

void ResetHandler::execute(GameNet::Box * box)
{
    game->getStadiumManager()->resetScore();
}
