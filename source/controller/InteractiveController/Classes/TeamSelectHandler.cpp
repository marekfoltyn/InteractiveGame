//
//  ConnectionLostHandler.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#include "TeamSelectHandler.h"
#include "BoxFactory.h"
#include "LobbyScene.h"


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
    
    // send to server
    auto team = button->getName();
    auto box = GameNet::BoxFactory::teamSelection(team);
    connector->send(box);
    
    // go to Lobby
    auto scene = LobbyScene::createScene();
    director->replaceScene(TransitionSlideInB::create(TIME_SCENE_TRANSITION, scene));
}