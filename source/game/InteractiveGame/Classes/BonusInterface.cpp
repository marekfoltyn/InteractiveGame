#include "BonusInterface.h"
#include "Game.h"

int BonusInterface::lastGeneratedId = 0;

BonusInterface::BonusInterface(Game * game)
{
    this->game = game;
    uniqueId = lastGeneratedId++;
    duration = DURATION_UNSET;
    durationMin = durationMax = ONE_TIME;
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
