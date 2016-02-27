//
//  Controller.cpp
//  InteractiveController
//
//  Created by Marek Foltýn on 24.02.16.
//
//

#include "Controller.h"

Controller * Controller::instance = nullptr;

Controller * Controller::getInstance()
{
    if(instance == nullptr)
    {
        return new Controller();
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
    handlerMap = HandlerMap::getInstance();
}

void Controller::run()
{
    bool netOk = startNetworking();
    if(!netOk){
        //TODO cant't start networking
    }
    
    //menuManager->runMainMenu();
}

bool Controller::startNetworking()
{
    // run  Connector (as a client)
    bool started = connector->start();
    connector->setServerName("PhoneBall Arena");
    
    if(!started){
        CCLOG("Connector not started!");
        return false;
    }
    
    director->getScheduler()->schedule([&](float dt)
    {
        this->receiveBoxes();
    },
    this, RECEIVE_TIMEOUT, CC_REPEAT_FOREVER, 0.0f, false, "receiveBoxes");
    
    return true;
}

void Controller::receiveBoxes()
{
    GameNet::Box * box;
    
    // c->receive() returns 0, if no received packet is in the queue
    while( (box = connector->receive()) != nullptr )
    {
        int type = box->getType();
        handlerMap->getBoxHandler(type)->execute(box);
        box->deallocate();
    }
}
