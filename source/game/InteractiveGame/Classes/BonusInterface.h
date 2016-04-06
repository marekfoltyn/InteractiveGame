#ifndef  _BonusInterface_H_
#define  _BonusInterface_H_

#include "cocos2d.h"
#include "Player.h"
class Game;

USING_NS_CC;

/**
 * interface representing general game bonus - it can be taken
 * from the pitch and activated by the player who took the bonus
 * usually the bonus can have lifetime - the effect last define amount of seconds
 * However, when effect lifetime is set to zero, it is a one-time bonus (for example add second ball)
 */
class BonusInterface{
public:
    
    constexpr static const float DURATION_UNSET = -1;
    constexpr static const float ONE_TIME = 0;
    
    BonusInterface();
    
    /**
     * bonus activation
     * @param playerId ID of the player who took the bonus
     * Better than using directly Player *, because when the user disconnects,
     * the player would be unallocated
     *
     * Don't forget to set this->playerId = playerId in activate(...)!
     */
    virtual void activate(int playerId) = 0;
    
    /**
     * bonus deactivation
     * used manually:
     *
     * BonusHandler manages scheduling, deactivation after gameover, etc.
     *
     * need to implement, when the bonus is not one-time (both durationMin and durationMax
     * are not zero)
     */
    virtual void deactivate(){}
    
    /**
     * bonus type name
     */
    std::string getName(){return name;}
    
    int getPlayerId(){return playerId;}
    
    /**
     * return unique bonus id
     */
    int id(){return uniqueId;}
    
    /**
     * get the game Sprite of the bonus
     * (with a PhysicsBody)
     */
    virtual Sprite * getSprite(){ return sprite; }
    
    /**
     * get the effect duration
     */
    float getDuration();

    virtual ~BonusInterface(){}
    
protected:
    
    /**
     * bonus name (must be unique among all bonus types!)
     * DON'T FORGET TO SET IN CONSTRUCTOR
     */
    std::string name;
    
    /**
     * unique bonus id (used in protobuf message)
     */
    int uniqueId;
    
    Game * game;
    
    /**
     * Sprite shown in the game
     */
    Sprite * sprite;
    
    /**
     * ID of the player who took this bonus
     */
    int playerId;
    
    /**
     * how long the bonus will have the effect
     * the minimum possible value
     */
    float durationMin;
    
    /**
     * how long the bonus will have the effect
     * the maximum possible value
     */
    float durationMax;
    
    /**
     * real already calculated effect duration
     */
    float duration;
    
    /**
     * generates a random duration value based
     * on durationMin and durationMax
     */
    float generateDuration()
    {
        return RandomHelper::random_real<float>(durationMin, durationMax);
    }

private:
    
    static int lastGeneratedId;

};


#endif // _BonusInterface_H_