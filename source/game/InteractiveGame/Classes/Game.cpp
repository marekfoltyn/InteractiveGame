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
    handlerMap = HandlerMap::create();
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
    stadiumManager->addExitButton( new ExitGameHandler(this) );
    
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
    connector->setServerName("Stadium 25");
    
    if(!started){
        CCLOG("Server not started!");
        return false;
    }

    director->getScheduler()->schedule(CC_CALLBACK_0(Game::receiveBoxes, this),
    this, RECEIVE_TIMEOUT, CC_REPEAT_FOREVER, 0.0f, false, "receiveBoxes");
    
    return true;
}



void Game::registerHandlers()
{
    auto logHandler = new LogHandler();
    auto disconnectHandler = new DisconnectHandler(this);
    auto kickHandler = new KickHandler(this);
    
    handlerMap->add(BOX_PLAYER_NAME, new NewPlayerHandler(this));
    handlerMap->add(BOX_ACCELERATION, new AccelerationBoxHandler(this));
    handlerMap->add(BOX_RESET_SCORE, new ResetHandler(this));
    handlerMap->add(BOX_DISCONNECTED, disconnectHandler);
    handlerMap->add(BOX_CONNECTION_LOST, disconnectHandler);
    handlerMap->add(BOX_PING, logHandler);
    handlerMap->add(BOX_NEW_CONNECTION, logHandler);
    handlerMap->add(BOX_KICK_PRESSED, kickHandler);
    handlerMap->add(BOX_KICK_RELEASED, kickHandler);
    
    stadiumManager->addCollisionHandler(BITMASK_PLAYER, new PlayerCollisionHandler(this) );
    //IDEA: scene->addCollisionHandler(BITMASK_GOAL_SCORE, new ScoreCollisionHandler(this) );
}



void Game::receiveBoxes()
{
    GameNet::Box * box;
    int type;
    bool finish = false;
    
    // c->receive() returns 0, if no received packet is in the queue
    while( (box = connector->receive()) != nullptr )
    {
        type = box->getType();
        finish = handlerMap->getBoxHandler(type)->execute(box); // Handler map returs always a valid handler
        box->deallocate();
        
        if(finish) break;
    }
}