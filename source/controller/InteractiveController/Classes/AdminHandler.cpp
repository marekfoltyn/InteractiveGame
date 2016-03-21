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
#include "LobbyScene.h"

AdminHandler::AdminHandler(LobbyScene * scene)
{
    director = Director::getInstance();
    controller = Controller::getInstance();
    this->scene = scene;
}

bool AdminHandler::execute( GameNet::Box * box )
{
    controller->setAdmin(true);
    
    if(scene != nullptr)
    {
        CCLOG("Showing admin button...");
        auto pause = scene->getChildByName(LobbyScene::NODE_PAUSE);
        pause->setVisible(true);
    }
    
    return false;
}