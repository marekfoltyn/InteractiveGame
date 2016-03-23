#ifndef  _TimedBonus_H_
#define  _TimedBonus_H_

#include "BonusInterface.h"
#include "cocos2d.h"

USING_NS_CC;

class TimedBonus : public BonusInterface{

    /**
     * activate() implemented, need to implement activateEffect(), deactivateEffect();
     */
    void activate(Player * player)
    {
        this->activateEffect(player);
        
        Director::getInstance()->getRunningScene()->schedule([this, player](float dt)
        {
            this->deactivateEffect(player);
        },
        generateDuration(), 0, 0.0f, "effectDeactivate");
    }
    
    /**
     * get the game Sprite of the bonus
     * (with a PhysicsBody)
     */
    virtual Sprite * getSprite() = 0;
    
protected:
    
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
     * effect activation
     */
    virtual void activateEffect(Player * player) = 0;
    
    /**
     * bonus deactivation after amount of time
     * (private because deactivation is automatic)
     */
    virtual void deactivateEffect(Player * player) = 0;
    
    /**
     * generates a random duration value based
     * on durationMin and durationMax
     */
    float generateDuration()
    {
        return RandomHelper::random_real<float>(durationMin, durationMax);
    }
    
};


#endif // _TimedBonus_H_