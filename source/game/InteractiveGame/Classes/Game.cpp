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
#include "GoalCollisionHandler.h"
#include "TeamSelectHandler.h"
#include "GameStateHandler.h"
#include "CountdownHandler.h"

#include "BoxFactory.h"

Game * Game::instance = nullptr;

Game::Game()
{
    director = cocos2d::Director::getInstance();
    connector = GameNet::Connector::getInstance();
    stadiumManager = StadiumManager::create();
    handlerMap = HandlerMap::create();
    admin = nullptr;
}


void Game::initGameState()
{
    gameState = GameState();
    gameState.set_pitchsize(GameState_PitchSize_SIZE_SMALL);
    gameState.set_duration(GameState_MatchDuration_DURATION_MEDIUM);
    gameState.set_state(GameState_State_STATE_LOBBY);
    setName(SERVER_NAME_DEFAULT);
}


Game * Game::getInstance()
{
    if(instance == nullptr)
    {
        instance = new Game();
    }
    
    return instance;
}



void Game::run()
{
    playing = false;
    stadiumManager->runStadium();
    stadiumManager->addExitButton( new ExitGameHandler(this) );
    
    registerHandlers();
    initGameState();
    stadiumManager->setSecondsLeft(durationToSeconds(GameState_MatchDuration_DURATION_MEDIUM));
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
    connector->setServerName(SERVER_NAME_DEFAULT);
    
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
    handlerMap->add(BOX_TEAM_SELECT, new TeamSelectHandler(this));
    handlerMap->add(BOX_ADMIN, new GameStateHandler());
    
    handlerMap->add(VOID_COUNTDOWN_FINISHED, new CountdownHandler());
    
    stadiumManager->addCollisionHandler(BITMASK_PLAYER, new PlayerCollisionHandler() );
    stadiumManager->addCollisionHandler(BITMASK_SCORE, new GoalCollisionHandler() );
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

std::string Game::getAutoTeam()
{
    int red  = 0;
    int blue = 0;
    
    // get team balance
    for(auto it = players.begin(); it != players.end(); ++it)
    {
        if(it->second->getTeam().compare(TEAM_BLUE) == 0)
        {
            blue++;
        }
        else if(it->second->getTeam().compare(TEAM_RED) == 0)
        {
            red++;
        }
    }
    
    if(red < blue)
    {
        return TEAM_RED;
    }
    else if( blue < red)
    {
        return TEAM_BLUE;
    }
    else
    {
        // randomly select team
        int random = RandomHelper::random_int(0, 1);
        return (random == 0) ? TEAM_BLUE : TEAM_RED;
    }
}



void Game::startBonusGenerating()
{
    //
    //handlerMap->add(VOID_GENERATE_BONUS, new BonusHandler(this));
    //handlerMap->getVoidHandler(VOID_GENERATE_BONUS)->execute();
}



void Game::stopBonusGenerating()
{
    
}



void Game::setAsAdmin(Player * player)
{
    admin = player;
    player->setAsAdmin();
    getStadiumManager()->setAdminName( player->getName() );
    CCLOG("%s", gameState.DebugString().c_str());
    auto box = GameNet::BoxFactory::admin( player->getAddress(), gameState );
    box->send();
}



void Game::setName(std::string name)
{
    connector->setServerName(name);
    gameState.set_name(name);
    stadiumManager->setServerName(name);
    
    CCLOG("GAME: name = %s", gameState.name().c_str());
    CCLOG("%s", gameState.DebugString().c_str());
}



void Game::setSize(GameState_PitchSize size)
{
    gameState.set_pitchsize(size);
//  stadiumManager->setSize(size);
    CCLOG("size: %d", gameState.pitchsize());
}



void Game::setDuration(GameState_MatchDuration duration)
{
    int seconds = durationToSeconds(duration);
    gameState.set_duration(duration);
    stadiumManager->setSecondsLeft( seconds );
    CCLOG("duration: %d", gameState.duration());
}



int Game::durationToSeconds(GameState_MatchDuration duration)
{
    if(duration == GameState_MatchDuration_DURATION_SHORT)
    {
        return Definitions::TIME_MATCH_SHORT;
    }

    if(duration == GameState_MatchDuration_DURATION_MEDIUM)
    {
        return Definitions::TIME_MATCH_MEDIUM;
    }

    if(duration == GameState_MatchDuration_DURATION_LONG)
    {
        return Definitions::TIME_MATCH_LONG;
    }

    return 0;
}



void Game::setCountdownEnabled(bool enabled)
{
    if(!enabled)
    {
        stadiumManager->getScene()->unschedule(SCHEDULE_COUNTDOWN);
        return;
    }
    
    // enabled == true
    stadiumManager->getScene()->schedule([&](float dt)
    {
        int secondsLeft = stadiumManager->getSecondsLeft();
        secondsLeft--;
        stadiumManager->setSecondsLeft(secondsLeft);

        // countdown finished
        if(secondsLeft == 0)
        {
            handlerMap->getVoidHandler(VOID_COUNTDOWN_FINISHED)->execute();
            gameState.set_state(GameState_State_STATE_LOBBY);
            
            // update admin's game state
            auto box = GameNet::BoxFactory::admin( admin->getAddress(), gameState );
            box->send();
        }
    },
    1, CC_REPEAT_FOREVER, 0.0f, SCHEDULE_COUNTDOWN);

}



void Game::startMatch()
{
    gameState.set_state(GameState_State_STATE_RUNNING);
    stadiumManager->setSecondsLeft(durationToSeconds(gameState.duration()));
    stadiumManager->matchMode();
    setCountdownEnabled(true);
    startBonusGenerating();
}



void Game::stopMatch()
{
    gameState.set_state(GameState_State_STATE_LOBBY);
    stadiumManager->lobbyMode();
    setCountdownEnabled(false);
    stopBonusGenerating();
}