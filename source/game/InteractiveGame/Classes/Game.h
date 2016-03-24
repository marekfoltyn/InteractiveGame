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
#include "AbstractHandlers.h"
#include "Player.h"
#include "StadiumScene.h"
#include "StadiumManager.h"
#include "HandlerMap.h"
#include "GameState.pb.h"

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
    
    /**
     * returns serialiable game information
     */
    GameState getState(){ return gameState; }
    
    /**
     * add a Player to the player map
     * (not to the stadium!)
     */
    void addPlayer(Player * player);
    
    /**
     * remove the Player from the player map
     * (not from the stadium!)
     */
    void removePlayer(Player * player);
    
    /**
     * returns players map size
     */
    int playersCount(){ return players.size(); }
    
    /**
     * returns nullptr if the players is not in the map
     */
    Player * getPlayer(int id);
    
    /**
     * returns a player (we can't determine which player)
     * not random function, usually returns always the same player!
     */
    Player * getRandomPlayer();
    
    /**
     * auto assigns team color
     * @return team color of the new player
     */
    std::string getAutoTeam();
    
    /**
     * start RakNet interface
     * returns false if there is a network error
     */
    bool startNetworking();
    
    /**
     * get the game state
     */
    bool isPlaying(){ return playing; }

    /**
     * StadiumManager getter
     */
    StadiumManager * getStadiumManager(){ return this->stadiumManager; }
    
    /**
     * once a while generate a bonus
     */
    void startBonusGenerating();
    
    /**
     * stop bonus generating and remove all bonuses from the game
     */
    void stopBonusGenerating();
    
    /**
     * set the Player as the admin and sends him game state information
     */
    void setAsAdmin(Player * player);
    
    /**
     * set new server name
     */
    void setName(std::string name);
    
    std::string getName(){ return gameState.name(); }
    /* IDEAS:
     
     void startBonusGenerating();
     void stopBonusGenerating();     // including removing bonuses in the pitch
     
     void startMatch();
     
     */

    
    
private:
    
    cocos2d::Director * director;
    GameNet::Connector * connector;
    
    /**
     * serializable game information
     */
    GameState gameState;
    
    /**
     * singleton instance
     */
    static Game * instance;
    
    /**
     * stadium manager - creates the stadium, resizes, manages player
     * in it and so on
     */
    StadiumManager * stadiumManager;
    
    /**
     * map of all game events
     */
    HandlerMap * handlerMap;
    
    /**
     * state of the stadium - lobby (false) or playing a match (true)
     */
    bool playing;
        
    /**
     * player map
     */
    std::map<int, Player *> players;
    
    Game();
    
    void initGameState();
    
    /**
     * add game handlers to the HandlerMap
     */
    void registerHandlers();
    
    /**
     * call BoxHandler to each received Box
     */
    void receiveBoxes();
    
};

#endif /* Game_h */
