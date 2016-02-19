//
//  Game
//  InteractiveGame
//
//  Created by Marek Foltýn on 18.02.16.
//
//

#include "Game.h"
#include "StadiumScene.h"

#include "NewPlayerHandler.h"

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
    scene = StadiumScene::createScene();
    director->runWithScene(scene);
    
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
    
    auto callback = cocos2d::CallFunc::create(CC_CALLBACK_0(Game::receiveBoxes, this));
    auto delay = cocos2d::DelayTime::create(RECEIVE_TIMEOUT);
    auto sequence = cocos2d::Sequence::create(callback, delay, nullptr);
    auto receivePacketAction = cocos2d::RepeatForever::create(sequence);
    scene->runAction(receivePacketAction);
    //director->getScheduler()->s
    return true;
}



void Game::registerBoxHandlers()
{
    boxHandlerMap[P_PLAYER_NAME] = new NewPlayerHandler(this);
}



void Game::receiveBoxes()
{
    GameNet::Box * box;
    
    // c->receive() returns 0, if no received packet is in the queue
    while( (box = connector->receive()) != nullptr )
    {
        int type = box->getType();
        if( boxHandlerMap.count(type) > 0){
            boxHandlerMap[type]->execute(box);
        }
    }
}