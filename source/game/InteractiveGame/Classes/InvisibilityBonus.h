#ifndef  _InvisibilityBonus_H_
#define  _InvisibilityBonus_H_

#include "TimedBonus.h"
#include "Game.h"

USING_NS_CC;

#define INVISIBILITY_MIN 60.0
#define INVISIBILITY_MAX 60.0
#define TIME_GAMESTREAM_DELAY 0.03
#define SCHEDULE_GAMESTREAM "gameStream"
#define BALL_COUNTDOWN 60
#define PLAYER_COUNTDOWN 31

class InvisibilityBonus: public TimedBonus {
public:
    
    static InvisibilityBonus * create();
    
    InvisibilityBonus();
        
protected:
    
    int playerCountdown;
    int ballCountdown;
    
    /**
     * effect activation
     */
    virtual void activateEffect(Player * player);
    
    /**
     * bonus deactivation after amount of time
     * (private because deactivation is automatic)
     */
    virtual void deactivateEffect(Player * player);
    
    Game * game;
    
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