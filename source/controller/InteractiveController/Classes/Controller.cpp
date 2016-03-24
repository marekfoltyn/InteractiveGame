//
//  Controller.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 24.02.16.
//
//

#include "Controller.h"
#include "GameplayDefinitions.h"


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
    
    GameState state = GameState();
}



bool Controller::startNetworking()
{
    // run  Connector as a client
    bool started = connector->start();
    
    if(!started){
        CCLOG("Connector not started!");
        return false;
    }
    
    return true;
}



void Controller::receiveBoxes(HandlerMap * handlerMap)
{
    GameNet::Box * box;
    
    // c->receive() returns 0, if no received packet is in the queue
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