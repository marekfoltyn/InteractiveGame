#ifndef  _BonusInterface_H_
#define  _BonusInterface_H_

#include "cocos2d.h"
#include "Player.h"

USING_NS_CC;

/**
 * interface representing general game bonus - it can be taken
 * from the pitch and activated by the player who took the bonus
 */
class BonusInterface{
public:

    /**
     * bonus activation
     * @param player Player who took the bonus
     */
    virtual void activate(Player * player) = 0;
    
    /**
     * get the game Sprite of the bonus
     * (with a PhysicsBody)
     */
    virtual Sprite * getSprite() = 0;
    

    virtual ~BonusInterface(){}
    
protected:
    
    /**
     * Sprite shown in the game
     */
    Sprite * sprite;

};


#endif // _BonusInterface_H_