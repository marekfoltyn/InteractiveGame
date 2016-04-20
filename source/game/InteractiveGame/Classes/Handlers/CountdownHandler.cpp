//
//  CountdownHandler.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#include "Game.h"
#include "CountdownHandler.h"

CountdownHandler::CountdownHandler(Game * game)
{
    this->game = game;
}



void CountdownHandler::execute()
{
    game->stopMatch();
}
