//
//  ConnectionLostHandler.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#include "ConnectionLostHandler.h"
#include "BoxFactory.h"

ConnectionLostHandler::ConnectionLostHandler(){}

void ConnectionLostHandler::execute( GameNet::Box * box )
{
    CCLOG("Connection lost. Returning to main menu.");
    
    // show next scene
    //menuManager->runMainMenu();
    
    //IDEA: menuManager->getMainMenuScene()->showConnectionLostWindow();
}