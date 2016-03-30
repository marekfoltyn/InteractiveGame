//
//  GameStreamHandler.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 29.02.16.
//
//

#include "GameplayDefinitions.h"
#include "GameStreamHandler.h"
#include "BoxFactory.h"
#include "ControlScene.h"

GameStreamHandler::GameStreamHandler(ControlScene * scene)
{
    director = Director::getInstance();
    controller = Controller::getInstance();
    this->scene = scene;
    
    auto actualStream = PBGameStream();
    actualStream.set_active(false);
}

bool GameStreamHandler::execute( GameNet::Box * box )
{
    auto stream = PBGameStream();
    auto message = box->getData();
    stream.ParseFromString(message);
    
    CCLOG("Game stream:");
    CCLOG("===========");
    CCLOG("%s", stream.DebugString().c_str());
    
    if( stream.has_active() )
    {
        updateActive( stream.active() );
    }
    
    return false;
}



void GameStreamHandler::updateActive(bool isActive)
{
    if(actualStream.active() == isActive){
        // nothing changed
        return;
    }
    
    setStadiumLayerVisible(isActive);
    actualStream.set_active(isActive);
}



void GameStreamHandler::setStadiumLayerVisible(bool visible)
{
    scene->getStadiumLayer()->setVisible(visible);
}