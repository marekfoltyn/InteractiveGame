#ifndef  _BonusInterface_H_
#define  _BonusInterface_H_

#include "cocos2d.h"
#include "Player.h"

USING_NS_CC;

/**
 * interface representing general game bonus - it can be taken
 * from the pitch and activated by the player who took the bonus
 * bonuses have various types - some of them last defined (but possibly variable)
 * amout of time and another are only one-time activated (for example: add a second ball)
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

private:
    
    /**
     * bonus deactivation (private because deactivation is automatic)
     */
    virtual void deactivate() = 0;
};


#endif // _BonusInterface_H_