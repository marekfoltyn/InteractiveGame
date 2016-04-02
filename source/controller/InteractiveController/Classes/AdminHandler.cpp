//
//  AdminHandler.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#include "GameplayDefinitions.h"
#include "AdminHandler.h"
#include "BoxFactory.h"
#include "ControlScene.h"

AdminHandler::AdminHandler(Node * scene)
{
    director = Director::getInstance();
    controller = Controller::getInstance();
    this->scene = scene;
}

bool AdminHandler::execute( GameNet::Box * box )
{
    controller->setAdmin(true);
    
    auto message = box->getData();
    controller->gameState.ParseFromString(message);
    
    CCLOG("Game state:");
    CCLOG("===========");
    CCLOG("%s", controller->gameState.DebugString().c_str());
    
    if(scene != nullptr)
    {
        CCLOG("Showing admin button...");
        auto pause = scene->getChildByName(BUTTON_ADMIN);
        pause->setVisible(true);
    }
    
    return false;
}