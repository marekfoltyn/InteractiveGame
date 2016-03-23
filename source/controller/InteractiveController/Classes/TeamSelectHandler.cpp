//
//  ConnectionLostHandler.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#include "TeamSelectHandler.h"
#include "BoxFactory.h"
#include "ControlScene.h"

TeamSelectHandler::TeamSelectHandler()
{
    director = Director::getInstance();
    connector = GameNet::Connector::getInstance();
}

void TeamSelectHandler::execute(Ref * sender, ui::Widget::TouchEventType type)
{
    if(type != ui::Widget::TouchEventType::ENDED){
        return;
    }
    
    auto button = dynamic_cast<ui::Button*>(sender);
    if(button == nullptr){
        CCLOG("Bad cast!!!");
        return;
    }
    
    // stop receiving packets to old scene
    director->getRunningScene()->unscheduleAllCallbacks();
    
    // send to server
    auto team = button->getName();
    auto box = GameNet::BoxFactory::teamSelection(team);
    connector->send(box);
    
    // go to Lobby
    auto newScene = ControlScene::createScene();
    director->replaceScene(TransitionSlideInB::create(TIME_SCENE_TRANSITION, newScene));
}