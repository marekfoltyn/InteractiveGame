//
//  ServerNameUpdateHandler.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#include "ServerNameUpdateHandler.h"
#include "BoxFactory.h"
#include "GameState.pb.h"

ServerNameUpdateHandler::ServerNameUpdateHandler()
{
    connector = Connector::getInstance();
    controller = Controller::getInstance();
}

void ServerNameUpdateHandler::execute(std::string name)
{
    GameState stateChange = GameState();
    
    // update local game state object
    controller->gameState.set_name(name);
    
    // send to server
    stateChange.set_name(name);
    BoxFactory::admin( connector->getServer(), stateChange)->send();
}