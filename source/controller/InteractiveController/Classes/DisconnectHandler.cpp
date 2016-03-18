//
//  ConnectionLostHandler.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#include "DisconnectHandler.h"
#include "MainMenuScene.h"
#include "WindowManager.h"

DisconnectHandler::DisconnectHandler()
{
    director = cocos2d::Director::getInstance();
    connector = GameNet::Connector::getInstance();
}

void DisconnectHandler::execute()
{

    auto server = connector->getServer();
    if( server != RakNet::UNASSIGNED_SYSTEM_ADDRESS )
    {
        connector->disconnect(server);
    }
    CCLOG("User disconnected. Returning to main menu.");
    Scene * main = MainMenuScene::createScene();
    director->replaceScene( TransitionSlideInT::create(TIME_SCENE_TRANSITION, main) );

}