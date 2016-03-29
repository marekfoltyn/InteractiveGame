//
//  CountdownHandler.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#include "Game.h"
#include "CountdownHandler.h"

CountdownHandler::CountdownHandler()
{
    game = Game::getInstance();
}



void CountdownHandler::execute()
{
    game->stopMatch();
}
