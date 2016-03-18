//
//  StartHandler.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#include "StartHandler.h"
#include "MainMenuScene.h"

#include "WindowManager.h"

StartHandler::StartHandler()
{
    controller = Controller::getInstance();
    director = Director::getInstance();
}



void StartHandler::execute()
{
    bool result = controller->startNetworking();
    if( result == false )
    {
        //IDEA: showStartFailedScene();
        return;
    }
    
    showMainMenu();
}



void StartHandler::showMainMenu()
{
    // create a scene. it's an autorelease object
    auto menu = MainMenuScene::createScene();
    director->runWithScene(menu);
  
    //auto scene = dynamic_cast<MainMenuScene*>(menu->getChildByTag(MainMenuScene::SCENE_TAG));
}