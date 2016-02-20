#include "ExitGameHandler.h"
#include "Game.h"

void ExitGameHandler::execute(void * data)
{
    game->end();
}
