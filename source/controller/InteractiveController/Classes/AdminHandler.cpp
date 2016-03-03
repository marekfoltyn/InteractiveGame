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
    this->scene = scene;
}

void AdminHandler::execute( GameNet::Box * box )
{
    CCLOG("Showing admin button...");
    auto pause = scene->getChildByName(LobbyScene::NODE_PAUSE);
    pause->setVisible(true);

}