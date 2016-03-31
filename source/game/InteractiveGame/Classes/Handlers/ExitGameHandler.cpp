#include "ExitGameHandler.h"
#include "Game.h"

ExitGameHandler::ExitGameHandler()
{
    game = Game::getInstance();
}

void ExitGameHandler::execute()
{
    game->end();
}
