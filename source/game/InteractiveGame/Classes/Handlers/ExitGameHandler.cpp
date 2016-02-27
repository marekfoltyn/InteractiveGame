#include "ExitGameHandler.h"
#include "Game.h"

void ExitGameHandler::execute()
{
    game->end();
}
