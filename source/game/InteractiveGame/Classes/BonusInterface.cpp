#include "BonusInterface.h"
#include "Game.h"

BonusInterface::BonusInterface()
{
    duration = DURATION_UNSET;
    durationMin = durationMax = ONE_TIME;
    game = Game::getInstance();
}


/**
 * get the effect duration
 */
float BonusInterface::getDuration()
{
    if( duration == DURATION_UNSET)
    {
        duration = generateDuration();
    }
    return duration;
}
