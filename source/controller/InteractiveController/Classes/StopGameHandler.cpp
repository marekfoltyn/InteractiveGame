//
//  StopGameHandler.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#include "StopGameHandler.h"
#include "GameplayDefinitions.h"
#include "BoxFactory.h"
#include "GameState.pb.h"

StopGameHandler::StopGameHandler()
{
    connector = Connector::getInstance();
    controller = Controller::getInstance();
}



void StopGameHandler::execute()
{
    
    // gameState difference
    GameState stateChange = GameState();
    stateChange.set_state(GameState_State_STATE_LOBBY);
    
    // update local game state object
    controller->gameState.set_state(GameState_State_STATE_LOBBY);
    
    // send to server
    BoxFactory::admin( connector->getServer(), stateChange)->send();
}