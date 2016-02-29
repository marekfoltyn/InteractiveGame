//
//  ServerNameHandler.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#include "ServerNameHandler.h"

ServerNameHandler::ServerNameHandler(MenuManager * manager)
{
    this->menuManager = manager;
}

void ServerNameHandler::execute( GameNet::Box * box )
{
     if( menuManager->isMainMenuRunning() )
     {
         CCLOG("Refreshing server...");
         menuManager->getMainMenuScene()->refreshServer(box);
     }
     else
     {
         CCLOG("ServerName ignored, menu is not running.");
     }
    
}