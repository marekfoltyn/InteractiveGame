//
//  ConnectionLostHandler.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#include "ConnectionLostHandler.h"
#include "MainMenuScene.h"
#include "WindowManager.h"

ConnectionLostHandler::ConnectionLostHandler()
{
    director = cocos2d::Director::getInstance();
}

bool ConnectionLostHandler::execute( GameNet::Box * box )
{
    CCLOG("Connection lost. Returning to main menu.");
    
    auto menu = MainMenuScene::createScene();
    director->replaceScene(menu);
    
    auto scene = dynamic_cast<MainMenuScene*>(menu->getChildByTag(MainMenuScene::SCENE_TAG));
    WindowManager::showConnectionLostDialog(scene);
    
    return false;
}