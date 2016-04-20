//
//  GameStateHandler.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#include "GameplayDefinitions.h"
#include "GameStateHandler.h"

GameStateHandler::GameStateHandler(Game * game)
{
    this->game = game;
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
    
    if( state.has_pitchsize() )
    {
        updateSize();
    }
    
    if( state.has_duration() )
    {
        updateDuration();
    }
    
    if( state.has_state() )
    {
        updateMatchState();
    }
    
    return false;
}



void GameStateHandler::updateName()
{
    game->setName( state.name() );
}



void GameStateHandler::updateSize()
{
    game->setSize( state.pitchsize() );
}



void GameStateHandler::updateDuration()
{
    game->setDuration( state.duration() );
}



void GameStateHandler::updateMatchState()
{
    if( state.state() == GameState_State_STATE_RUNNING)
    {
        game->startMatch();
        return;
    }
    
    if( state.state() == GameState_State_STATE_LOBBY)
    {
        game->stopMatch();
        return;
    }
}