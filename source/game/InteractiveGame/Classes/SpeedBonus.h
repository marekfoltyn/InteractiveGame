#ifndef  _SpeedBonus_H_
#define  _SpeedBonus_H_

#include "BonusInterface.h"

USING_NS_CC;

#define SPEEDBONUS_MIN 5.0
#define SPEEDBONUS_MAX 20.0
#define SPEEDBONUS_MULTIPLIER 0.4

class SpeedBonus: public BonusInterface {
public:
    
    static SpeedBonus * create();
    
    SpeedBonus(Game *);
        
protected:
    
    /**
     * effect activation
     */
    virtual void activate(int playerId);
    
    /**
     * effect deactivation
     */
    virtual void deactivate();
};


#endif // _SpeedBonus_H_