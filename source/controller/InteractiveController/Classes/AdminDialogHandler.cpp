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

    if(controller->gameState.state() == GameState_State_STATE_RUNNING){
        WindowManager::showStopGame(scene, controller->gameState, handlerMap);
    } else {
        WindowManager::showAdminSettings(scene, controller->gameState, handlerMap );
    }
}