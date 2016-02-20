//
//  Game
//  InteractiveGame
//
//  Created by Marek Foltýn on 18.02.16.
//
//

#ifndef Game_h
#define Game_h

#include "cocos2d.h"
#include "Connector.h"
#include "BoxHandler.h"
#include "Player.h"
#include "StadiumScene.h"
#include "StadiumManager.h"

#include <map>

/**
 * singleton class representing general game
 * it cooperates with other game objects and coordinates them
 * this is the "entry point" of the game logic
 */
class Game{
public:
    
    static Game * getInstance();
    
    /**
     * called when the Stadium is launched
     */
    void run();
    
    /**
     * called when player wants to end the game
     */
    void end();
    
    StadiumScene * getScene(){ return this->scene; }
    
private:
    
    static Game * instance;
    
    StadiumScene * scene;
    StadiumManager * stadiumManager;
    cocos2d::Director * director;
    GameNet::Connector * connector;
    
    std::map<int, BoxHandler *> boxHandlerMap;
    std::map<int, Player *> players;
    
    Game();
    
    bool startNetworking();
    void registerBoxHandlers();
    void receiveBoxes();
    
};

#endif /* Game_h */
