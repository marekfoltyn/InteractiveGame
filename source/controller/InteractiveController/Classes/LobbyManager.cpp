//
//  LobbyManager.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 27.02.16.
//
//

#include "LobbyManager.h"

LobbyManager * LobbyManager::instance = nullptr;

LobbyManager * LobbyManager::getInstance()
{
    if(instance == nullptr)
    {
        return new LobbyManager();
    }
    else
    {
        return instance;
    }
}



LobbyManager::LobbyManager()
{
    director = cocos2d::Director::getInstance();
    handlerMap = HandlerMap::getInstance();

    lobbyScene = nullptr;
}



void LobbyManager::runLobby()
{
    // create a scene. it's an autorelease object
    auto scene = LobbyScene::createScene();
    
    // run
    director->replaceScene(scene);
}



bool LobbyManager::isLobbyRunning()
{
    return getLobbyScene() != nullptr;
}



LobbyScene * LobbyManager::getLobbyScene()
{
    auto scene = director->getRunningScene()->getChildByTag<LobbyScene*>(LobbyScene::SCENE_TAG);
    return scene;
}
