//
//  PingServersHandler.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#include "PingServersHandler.h"
#include "MainMenuScene.h"

PingServersHandler::PingServersHandler()
{
    controller = Controller::getInstance();
    director = Director::getInstance();
}



void PingServersHandler::execute()
{
    CCLOG("FAKE pinging...");
}