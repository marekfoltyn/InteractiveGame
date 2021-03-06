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
#include "HandlerMap.h"
#include "GameState.pb.h"
class BonusHandler;

#include <map>
#include <set>

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
     * get the StadiumScene object
     */
    StadiumScene * getStadium(){ return stadium; }
    
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
     * set the Player as the admin and sends him game state information
     */
    void setAsAdmin(Player * player);
    
    /**
     * set new server name
     */
    void setName(std::string name);
    std::string getName(){ return gameState.name(); }
    
    /**
     * set new server size
     */
    void setSize(GameState_PitchSize size);
    
    /**
     * set new match duration
     */
    void setDuration(GameState_MatchDuration);
    
    /**
     * begin the match
     */
    void startMatch();
    
    /**
     * force stop the match
     */
    void stopMatch();
    
    /**
     * start/stop match countdown
     * when countdown is finished, it calls handler for VOID_COUNTDOWN_FINISHED
     */
    void setCountdownEnabled(bool enabled);
        
    /**
     * map of players
     * USE FOR READING ONLY! For editing, use addPlaye(...) or removePlayer(...)
     */
    std::map<int, Player *> players;
    
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
     * map of all game events
     */
    HandlerMap * handlerMap;
    
    /**
     * state of the stadium - lobby (false) or playing a match (true)
     */
    bool playing;
    
    /**
     * stadium scene
     */
    StadiumScene * stadium;
    
    /**
     * pointer of the admin player
     */
    Player * admin;
    
    /**
     * bonus handler object
     */
    BonusHandler * bonusHandler;
    
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
    
    /**
     * helper method - conversion between gameState and seconds
     */
    int durationToSeconds(GameState_MatchDuration duration);
    
};

#endif /* Game_h */
