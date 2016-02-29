//
//  Game
//  InteractiveGame
//
//  Created by Marek Foltýn on 18.02.16.
//
//

#include "GameplayDefinitions.h"

#include "Game.h"
#include "StadiumScene.h"

#include "AccelerationBoxHandler.h"
#include "NewPlayerHandler.h"
#include "DisconnectHandler.h"
#include "ExitGameHandler.h"
#include "LogHandler.h"
#include "ResetHandler.h"
#include "KickHandler.h"
#include "PlayerCollisionHandler.h"

Game * Game::instance = nullptr;

Game::Game()
{
    director = cocos2d::Director::getInstance();
    connector = GameNet::Connector::getInstance();
    
    stadiumManager = StadiumManager::create();
    
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
    stadiumManager->runStadium();
    scene = stadiumManager->getScene();
    stadiumManager->addExitButton( new ExitGameHandler(this) );
    
    bool netOk = startNetworking();
    if(!netOk){
        //TODO cant't start networking, show alert and exit
    }
    
    registerHandlers();
}



void Game::end()
{
    connector->stop();
    director->end();
    exit(0);
}



void Game::addPlayer(Player * player)
{
    int id = player->getId();
    players[id] = player;
}



void Game::removePlayer(Player * player)
{
    auto iterator = players.find( player->getId() );
    if( iterator != players.end())
    {
        int sizeBefore = players.size();
        std::string name = player->getName();
        players.erase(iterator);
        int sizeAfter = players.size();
        
        if(sizeBefore > sizeAfter){
            CCLOG("Player %s was removed from game", name.c_str());
        } else {
            CCLOG("Player %s was NOT removed from game", name.c_str());
        }
        
    }
}



Player * Game::getPlayer(int id)
{
    auto iterator = players.find(id);
    if( iterator != players.end())
    {
        return iterator->second;
    }
    return nullptr;
}


Player * Game::getRandomPlayer()
{
    return players.begin()->second;
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



void Game::registerHandlers()
{
    auto logHandler = new LogHandler();
    auto disconnectHandler = new DisconnectHandler(this);
    
    boxHandlerMap[BOX_PLAYER_NAME] = new NewPlayerHandler(this);
    boxHandlerMap[BOX_ACCELERATION] = new AccelerationBoxHandler(this);
    boxHandlerMap[BOX_RESET_SCORE] = new ResetHandler(this);
    boxHandlerMap[BOX_DISCONNECTED] = disconnectHandler;
    boxHandlerMap[BOX_CONNECTION_LOST] = disconnectHandler;

    boxHandlerMap[BOX_PING] = logHandler;
    boxHandlerMap[BOX_NEW_CONNECTION] = logHandler;
    auto kickHandler = new KickHandler(this);
    boxHandlerMap[BOX_KICK_PRESSED] = kickHandler;
    boxHandlerMap[BOX_KICK_RELEASED] = kickHandler;
    
    stadiumManager->addCollisionHandler(BITMASK_PLAYER, new PlayerCollisionHandler(this) );
    //TODO: scene->addCollisionHandler(BITMASK_GOAL_SCORE, new ScoreCollisionHandler(this) );
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