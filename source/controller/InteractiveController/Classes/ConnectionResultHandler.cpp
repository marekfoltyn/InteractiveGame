//
//  ConnectionResultHandler.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#include "GameplayDefinitions.h"
#include "ConnectionResultHandler.h"
#include "BoxFactory.h"
#include "TeamScene.h"
#include "MainMenuScene.h"

ConnectionResultHandler::ConnectionResultHandler(MainMenuScene * scene)
{
    director = Director::getInstance();
    this->scene = scene;
}

bool ConnectionResultHandler::execute( GameNet::Box * box )
{
    int type = box->getType();
    if( type == BOX_CONNECTION_FAILED)
    {
        CCLOG("Connection failed");
        scene->setLoadingAnimation(false);
        Device::vibrate(0.5);
    }
    else if( type == BOX_CONNECTED)
    {
        // send player's name
        UserDefault * def = UserDefault::getInstance();
        std::string name = def->getStringForKey("player_name", "noname");
        GameNet::BoxFactory::playerName(name)->send();
    
        CCLOG("Connected to %s", box->getAddress().ToString());
        
        // stop receiving packets to old scene
        scene->unscheduleAllCallbacks();
        
        // show next scene
        auto nextScene = TeamScene::createScene();
        director->replaceScene(TransitionSlideInB::create(TIME_SCENE_TRANSITION, nextScene));
        
        // stop receiving loop (the rest will receive next scene)
        return true;
    }
    
    return false;
}