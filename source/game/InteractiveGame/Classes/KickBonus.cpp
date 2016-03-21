#include "KickBonus.h"
#include "GameplayDefinitions.h"

KickBonus::KickBonus()
{
    sprite = nullptr;
    durationMin = Definitions::TIME_KICKBONUS_MIN;
    durationMax = Definitions::TIME_KICKBONUS_MAX;
}


void KickBonus::activateEffect(Player * player)
{
    player->setKickMultiplier(Definitions::KICKBONUS_MULTIPLIER);
    //BoxFactory::KickBonusActivated(player)->send();
}



Sprite * KickBonus::getSprite()
{
    auto sprite = Sprite::create("bonus_kick.png");
    
    
    return sprite;
}



void KickBonus::deactivateEffect(Player * player)
{
    //BoxFactory::KickBonusDeactivated(player)->send();
    player->setKickMultiplier(1);
}

