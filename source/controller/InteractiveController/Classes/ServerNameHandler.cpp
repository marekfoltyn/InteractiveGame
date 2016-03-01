//
//  ServerNameHandler.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#include "ServerNameHandler.h"
#include "ServerNameMessage.h"
#include "MainMenuScene.h"

ServerNameHandler::ServerNameHandler()
{
    controller = Controller::getInstance();
}

void ServerNameHandler::execute( GameNet::Box * box )
{
    if( !controller->isRunning<MainMenuScene>() )
    {
        CCLOG("MainMenu is not running, ServerName ignored.");
        return;
    }
    
    auto message = ServerNameMessage();
    message.deserialize(box->getData());
    auto name = message.getServerName();
    CCLOG("Server ping: %s", name.c_str());
         
    auto scene = controller->getScene<MainMenuScene>();
    scene->refreshServer(box);
}