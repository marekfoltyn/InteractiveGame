#ifndef  _InvisibilityBonus_H_
#define  _InvisibilityBonus_H_

#include "BonusInterface.h"
#include "Game.h"

USING_NS_CC;

#define INVISIBILITY_MIN 10.0
#define INVISIBILITY_MAX 10.0
#define TIME_GAMESTREAM_DELAY 0.015
#define SCHEDULE_GAMESTREAM "gameStream"
#define BALL_COUNTDOWN 15
#define PLAYER_COUNTDOWN 29

class InvisibilityBonus: public BonusInterface {
public:
    
    static InvisibilityBonus * create();
    
    InvisibilityBonus();
        
protected:
    
    int playerCountdown;
    int ballCountdown;
    
    /**
     * effect activation
     */
    virtual void activate(int playerId);
    
    /**
     * effect deactivation
     */
    virtual void deactivate();
    
    Game * game;
    cocos2d::Director * director;
    
    /**
     * sending game information necessary for
     * game rendering on mobile screen
     * 
     * if last is true, GameStream object will notify
     * the player that it is the last GameStream packet
     * and that it should disable game rendering and go 
     * back to ControlScene
     */
    void sendInitialGameStream(Player * player);
    void sendGameStreamDelta(Player * player);
    void sendLastGameStream(Player * player);
};


#endif // _InvisibilityBonus_H_