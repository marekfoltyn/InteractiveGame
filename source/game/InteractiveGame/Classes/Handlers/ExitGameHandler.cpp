#include "ExitGameHandler.h"
#include "Game.h"

ExitGameHandler::ExitGameHandler(Game * game)
{
    this->game = game;
}

void ExitGameHandler::execute()
{
    game->end();
}
