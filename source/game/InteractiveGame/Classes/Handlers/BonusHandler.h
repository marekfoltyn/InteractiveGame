#ifndef  _BonusHandler_H_
#define  _BonusHandler_H_

#include "Box.h"
#include "AbstractHandlers.h"
#include "StadiumScene.h"
#include "BonusInterface.h"
#include <string>
#include <set>
class Game;

/**
 * combined handler - it has three main functions
 * 1) bonus generation - try to generate a bonus and place it into the stadium
 * 2) bonus collision - take the bonus and apply effect
 * 3) activation and deactivation of the bonuses (with networking)
 *
 * Notes:
 * When user takes two same bonuses, the first is deactivated and the new bonus
 * is activated
 */
class BonusHandler: public CollisionHandler{
public:
    
    BonusHandler();
    
    /**
     * enabling / disabling bonus generation
     * once a while it generates a bonus and places it into
     * the stadium
     */
    void setBonusDaemonEnabled(bool enabled);
    
    /**
     * runs every second (when bonus daemon enabled)
     * and generates a bonus with PROBABILITY_BONUS probability
     */
    void probabilityGeneration();
    
    /**
     * bonus collision - a Player took a bonus
     */
    void execute(PhysicsBody * first, PhysicsBody * second);
    
    /**
     * bonus deactivation
     */
    void deactivate(BonusInterface * bonus);
    
    /**
     * generates all bonuses for debug purposes
     */
    void generateDebugBonuses();
    
private:
    
    Game * game;
    StadiumScene * stadium;
    Director * director;
    
    /**
     * set of active bonuses
     */
    std::set<BonusInterface *> activeBonuses;
    
    /**
     * debug - generate all bonuses at once
     */
    EventListenerKeyboard * debugListener;
    
    /**
     * generate a random bonus object
     */
    BonusInterface * generateBonus();

    /**
     * place bonus to specified position
     * and schedule for automatic deletion
     */
    void placeBonus(BonusInterface * bonus, Vec2 position);
    
    /**
     * generate random position in the stadium
     */
    Vec2 generatePosition();
    
    
    
    
};

#endif // _BonusHandler_H_