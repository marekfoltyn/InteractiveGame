//
//  ConnectionResultHandler.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#include "GameplayDefinitions.h"
#include "ConnectionResultHandler.h"
#include "BoxFactory.h"

ConnectionResultHandler::ConnectionResultHandler(){}

void ConnectionResultHandler::execute( GameNet::Box * box )
{
    int type = box->getType();
    if( type == BOX_CONNECTION_FAILED)
    {
        CCLOG("Connection failed");
        //menuManager->getMainMenuScene()->connectionFailed(box);
    }
    else if( type == BOX_CONNECTED)
    {
        // send player's name
        UserDefault * def = UserDefault::getInstance();
        std::string name = def->getStringForKey("player_name", "noname");
        GameNet::BoxFactory::playerName(name)->send();
    
        CCLOG("Connected to %s", box->getAddress().ToString());
    
        // show next scene
        //lobbyManager->runLobby();
    }
}