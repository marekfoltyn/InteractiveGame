//
//  StartGameHandler.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#include "StartGameHandler.h"
#include "GameplayDefinitions.h"
#include "BoxFactory.h"
#include "GameState.pb.h"

StartGameHandler::StartGameHandler()
{
    connector = Connector::getInstance();
    controller = Controller::getInstance();
}



void StartGameHandler::execute()
{
    
    // gameState difference
    GameState stateChange = GameState();
    stateChange.set_state(GameState_State_STATE_RUNNING);
    
    // update local game state object
    controller->gameState.set_state(GameState_State_STATE_RUNNING);
    
    // send to server
    BoxFactory::admin( connector->getServer(), stateChange)->send();
}