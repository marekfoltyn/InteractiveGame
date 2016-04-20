#ifndef  _KickBonus_H_
#define  _KickBonus_H_

#include "BonusInterface.h"

USING_NS_CC;

class KickBonus: public BonusInterface {
public:
    
    static KickBonus * create();
    
    KickBonus(Game *);
        
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


#endif // _KickBonus_H_