#ifndef  _SpeedBonus_H_
#define  _SpeedBonus_H_

#include "TimedBonus.h"

USING_NS_CC;

#define SPEEDBONUS_MIN 5.0
#define SPEEDBONUS_MAX 20.0
#define SPEEDBONUS_MULTIPLIER 0.4

class SpeedBonus: public TimedBonus {
public:
    
    static SpeedBonus * create();
    
    SpeedBonus();
        
protected:
    
    /**
     * effect activation
     */
    virtual void activateEffect(Player * player);
    
    /**
     * bonus deactivation after amount of time
     * (private because deactivation is automatic)
     */
    virtual void deactivateEffect(Player * player);
};


#endif // _SpeedBonus_H_