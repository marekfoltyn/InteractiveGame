//
//  Controller.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 24.02.16.
//
//

#include "Controller.h"
#include "GameplayDefinitions.h"
#include "BoxFactory.h"


Controller * Controller::instance = nullptr;



Controller * Controller::getInstance()
{
    if(instance == nullptr)
    {
        return instance = new Controller();
    }
    else
    {
        return instance;
    }
}

Controller::Controller()
{
    director = cocos2d::Director::getInstance();
    connector = GameNet::Connector::getInstance();
    
    admin = false;
    speedScale = 1;
    GameState state = GameState();
}



bool Controller::startNetworking()
{
    // run  Connector as a client
    bool started = connector->startAsClient();
    
    if(!started){
        CCLOG("Connector not started!");
        return false;
    }
    
    return true;
}



void Controller::receiveBoxes(HandlerMap * handlerMap)
{
    GameNet::Box * box;
    
    // c->receive() returns nullptr, when no received packet is in the queue
    bool finish = false;
    while( (box = connector->receive()) != nullptr )
    {
        int type = box->getType();
        finish = handlerMap->getBoxHandler(type)->execute(box);
        box->deallocate();
        
        if(finish) break;
    }
}


void Controller::setVibrate(bool set)
{
    UserDefault * def = UserDefault::getInstance();
    def->setBoolForKey(SETTINGS_VIBRATE, set);
    if(set) Device::vibrate(Definitions::TIME_VIBRATION_ENABLED);
}



bool Controller::isVibrateEnabled()
{
    UserDefault * def = UserDefault::getInstance();
    return def->getBoolForKey(SETTINGS_VIBRATE, true);
}



void Controller::setAdmin(bool status)
{
    admin = status;
}



std::string Controller::getServerName()
{
    if( gameState.has_name() )
    {
        return gameState.name();
    }
    else
    {
        return "";
    }
}



void Controller::setServerName( std::string name )
{
    GameState stateChange = GameState();
    stateChange.set_name(name);
}



void Controller::pushStadium()
{
    // prepare stadium scene
    directorStadium = StadiumScene::createScene();
    director->pushScene(directorStadium);
    stadium = directorStadium->getChildByTag<StadiumScene*>(StadiumScene::SCENE_TAG);
}



void Controller::popStadium()
{
    director->popScene();
}



void Controller::setSpeedScale(float scale)
{
    if( scale < 0){
        speedScale = 0;
    } else {
        speedScale = scale;
    }
}





















