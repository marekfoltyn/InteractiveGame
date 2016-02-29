//
//  ServerNameHandler.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#include "ServerNameHandler.h"
#include "ServerNameMessage.h"

ServerNameHandler::ServerNameHandler(){}

void ServerNameHandler::execute( GameNet::Box * box )
{
     /*if( menuManager->isMainMenuRunning() )
     {
         auto message = ServerNameMessage();
         message.deserialize(box->getData());
         auto name = message.getServerName();
         CCLOG("Server ping: %s", name.c_str());
         
         menuManager->getMainMenuScene()->refreshServer(box);
     }
     else
     {
         CCLOG("ServerName ignored, menu is not running.");
     }*/
}