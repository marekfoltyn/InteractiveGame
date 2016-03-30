#ifndef  _KickBonus_H_
#define  _KickBonus_H_

#include "TimedBonus.h"

USING_NS_CC;

class KickBonus: public TimedBonus {
public:
    
    static KickBonus * create();
    
    KickBonus();
        
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


#endif // _KickBonus_H_