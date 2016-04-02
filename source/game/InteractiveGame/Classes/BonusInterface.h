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
     * bonus deactivation
     * used both automatically and manually:
     *
     * - after bonus lifetime it will automatically deactivates the bonus
     *   (when nothing unusuall happens)
     *
     * - when game over, it is necessary to deactivate
     *   bonus manually
     */
    //virtual void deactivate();
    
    /**
     * get the game Sprite of the bonus
     * (with a PhysicsBody)
     */
    virtual Sprite * getSprite(){ return sprite; }
    

    virtual ~BonusInterface(){}
    
protected:
    
    /**
     * Sprite shown in the game
     */
    Sprite * sprite;

};


#endif // _BonusInterface_H_