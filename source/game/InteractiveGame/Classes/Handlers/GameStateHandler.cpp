//
//  GameStateHandler.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#include "GameplayDefinitions.h"
#include "GameStateHandler.h"

GameStateHandler::GameStateHandler()
{
    game = Game::getInstance();
}

bool GameStateHandler::execute( GameNet::Box * box )
{
    auto message = box->getData();
    state = GameState();
    state.ParseFromString(message);
    
    CCLOG("Game state change:");
    CCLOG("===========");
    CCLOG("%s", state.DebugString().c_str());
    
    if( state.has_name() )
    {
        updateName();
    }
    
    return false;
}



void GameStateHandler::updateName()
{
    CCLOG("new name: %s", state.name().c_str());
    game->setName( state.name() );
}