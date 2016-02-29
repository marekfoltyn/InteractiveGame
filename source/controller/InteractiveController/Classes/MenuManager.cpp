//
//  MenuManager.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 27.02.16.
//
//

#include "MenuManager.h"
#include "ServerListScene.h"
#include "ServerNameHandler.h"

MenuManager * MenuManager::instance = nullptr;

MenuManager * MenuManager::getInstance()
{
    if(instance == nullptr)
    {
        return instance = new MenuManager();
    }
    else
    {
        return instance;
    }
}



MenuManager::MenuManager()
{
    director = cocos2d::Director::getInstance();
    handlerMap = HandlerMap::getInstance();
    this->mainMenuScene = nullptr;
    
    // register handlers
    handlerMap->add(BOX_SERVER_NAME, new ServerNameHandler(this) );
}



void MenuManager::runMainMenu()
{
    // create a scene. it's an autorelease object
    auto scene = ServerListScene::createScene();
    
    // run
    director->replaceScene(scene);
}



void MenuManager::startWithMainMenu()
{
    // create a scene. it's an autorelease object
    auto scene = ServerListScene::createScene();
    
    // run
    director->runWithScene(scene);
}



bool MenuManager::isMainMenuRunning()
{
    return getMainMenuScene() != nullptr;
}

ServerListScene * MenuManager::getMainMenuScene()
{
    auto scene = director->getRunningScene()->getChildByTag<ServerListScene*>(ServerListScene::SCENE_TAG);
    return scene;
}
