//
//  Game
//  InteractiveGame
//
//  Created by Marek Foltýn on 18.02.16.
//
//

#include "Game.h"
#include "StadiumScene.h"

#include "AccelerationHandler.h"
#include "NewPlayerHandler.h"
#include "DisconnectHandler.h"
#include "ExitGameHandler.h"
#include "LogHandler.h"
#include "ResetHandler.h"
#include "KickHandler.h"
#include "TackleHandler.h"

Game * Game::instance = nullptr;

Game::Game()
{
    director = cocos2d::Director::getInstance();
    connector = GameNet::Connector::getInstance();
    
    boxHandlerMap = std::map<int, BoxHandler*>();
}



Game * Game::getInstance()
{
    if(instance == nullptr)
    {
        return new Game();
    }
    else
    {
        return instance;
    }
}



void Game::run()
{
    auto scene = StadiumScene::createScene();
    director->runWithScene(scene);
    // get the StadiumScene object (StadiumScene::createScene() creates a general Scene*)
    this->scene = dynamic_cast<StadiumScene*>(scene->getChildByTag(StadiumScene::SCENE_TAG));
    this->scene->addExitHandler( new ExitGameHandler(this) );
    
    stadiumManager = StadiumManager::create(this->scene);
    stadiumManager->setPitch();
    
    bool netOk = startNetworking();
    if(!netOk){
        //TODO cant't start networking
    }
    
    registerBoxHandlers();
}



void Game::end()
{
    connector->stop();
    director->end();
    exit(0);
}



bool Game::startNetworking()
{
    // run  Connector (as a server)
    bool started = connector->startAsServer(MAX_PLAYERS);
    connector->setServerName("PhoneBall Arena");
    
    if(!started){
        CCLOG("Server not started!");
        return false;
    }

    director->getScheduler()->schedule([&](float dt)
    {
        this->receiveBoxes();
    },
    this, RECEIVE_TIMEOUT, CC_REPEAT_FOREVER, 0.0f, false, "receiveBoxes");
    
    return true;
}



void Game::registerBoxHandlers()
{
    auto logHandler = new LogHandler();
    auto disconnectHandler = new DisconnectHandler(this);
    
    boxHandlerMap[P_PLAYER_NAME] = new NewPlayerHandler(this);
    boxHandlerMap[P_ACCELERATION] = new AccelerationHandler(this);
    boxHandlerMap[P_RESET_SCORE] = new ResetHandler(this);
    boxHandlerMap[P_DISCONNECTED] = disconnectHandler;
    boxHandlerMap[P_CONNECTION_LOST] = disconnectHandler;

    boxHandlerMap[P_PING] = logHandler;
    boxHandlerMap[P_NEW_CONNECTION] = logHandler;
    boxHandlerMap[P_KICK] = new KickHandler(this);
    boxHandlerMap[P_TACKLE] = new TackleHandler(this);
}



void Game::receiveBoxes()
{
    GameNet::Box * box;
    
    // c->receive() returns 0, if no received packet is in the queue
    while( (box = connector->receive()) != nullptr )
    {
        int type = box->getType();
        if( boxHandlerMap.count(type) > 0)
        {
            boxHandlerMap[type]->execute(box);
        }
        box->deallocate();
    }
}