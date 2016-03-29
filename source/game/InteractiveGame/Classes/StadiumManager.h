//
//  StadiumManager
//  InteractiveGame
//
//  Created by Marek Foltýn on 05.02.16.
//
//

#ifndef StadiumManager_h
#define StadiumManager_h

#include "cocos2d.h"
#include "StadiumScene.h"
#include "AbstractHandlers.h"
#include "Player.h"


/**
 * class that manages stadium - constructs and modifies object in it
 * cooperating with the Scene and game logic (bonuses, pitch scaling, ...)
 */
class StadiumManager{
public:
    
    static StadiumManager * create();
    
    void drawPitch();
    
    void addExitButton( VoidHandler * handler );
    
    void addNewPlayer(Player * player);
    
    void showPlayer(Player * player);
    
    void removePlayer(Player * player);
    
    void setAdminName(std::string name);
    
    void setServerName(std::string name);
    
    void setSecondsLeft(int seconds);
    int getSecondsLeft(){ return secondsLeft; }
    
    void resetScore();
    
    void runStadium();
    
    void addCollisionHandler(int bitmask, CollisionHandler * handler);
    
    void matchMode();
    
    void lobbyMode();
    
    void setBallEnabled(bool enabled);
    
    /* IDEAS:
     
    void setPitchSize(PitchSize size);
     
    void prepareLobby();
     
    void prepareMatch();
     
    
     
     */
    
    StadiumScene * getScene(){return scene; }
    
private:
    
    StadiumManager();
    
    StadiumScene * scene;
    cocos2d::Director * director;

    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;

    int secondsLeft;
    
    Label * leftScore;
    Label * rightScore;
    Label * lblAdmin;
    Label * lblAdminName;
    Label * lblServerName;
    Label * lblTime;
    Label * btnExit;
    
    void setLabelsTransparent(bool transparent);
    
    /* IDEAS:
     
    PitchSize pitchSize;
    
    void removeBonuses();
     
    void setPlayerListEnabled(bool enabled);
    
    void setGameResultEnabled(bool enabled);
    
     
     
     */
    
};

#endif /* StadiumManager_h */
