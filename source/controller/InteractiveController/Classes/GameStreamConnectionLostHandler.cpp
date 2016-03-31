//
//  GameStreamConnectionLostHandler
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#include "GameStreamConnectionLostHandler.h"
#include "MainMenuScene.h"
#include "WindowManager.h"
#include "GameStreamHandler.h"

GameStreamConnectionLostHandler::GameStreamConnectionLostHandler(StadiumScene * stadium)
{
    director = cocos2d::Director::getInstance();
    this->stadium = stadium;
}

bool GameStreamConnectionLostHandler::execute( GameNet::Box * box )
{
    CCLOG("Connection lost. Returning to main menu.");
    
    auto menu = MainMenuScene::createScene();
    
    // stop networking
    director->getScheduler()->unschedule(SCHEDULE_NETWORKING, stadium);
    
    // pop stadium scene
    director->popScene();
    director->replaceScene(menu);
    
    auto scene = dynamic_cast<MainMenuScene*>(menu->getChildByTag(MainMenuScene::SCENE_TAG));
    WindowManager::showConnectionLostDialog(scene);
    
    return false;
}