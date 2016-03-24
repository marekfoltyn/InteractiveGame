//
//  AdminDialogHandler.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#include "AdminDialogHandler.h"
#include "WindowManager.h"

AdminDialogHandler::AdminDialogHandler(HandlerMap * handlerMap)
{
    director = cocos2d::Director::getInstance();
    connector = GameNet::Connector::getInstance();
    controller = Controller::getInstance();
    this->handlerMap = handlerMap;
}

void AdminDialogHandler::execute()
{
    auto scene = director->getRunningScene();
    WindowManager::showAdminSettings(scene, controller->gameState, handlerMap );
}