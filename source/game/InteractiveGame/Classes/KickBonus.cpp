#include "KickBonus.h"
#include "GameplayDefinitions.h"

KickBonus * KickBonus::create()
{
    return new KickBonus();
}

KickBonus::KickBonus()
{
    durationMin = Definitions::TIME_KICKBONUS_MIN;
    durationMax = Definitions::TIME_KICKBONUS_MAX;

    sprite = Sprite::create("bonus_kick.png");
    sprite->setScale(0.5);
    sprite->setName(LABEL_BONUS);
    
    auto body = cocos2d::PhysicsBody::createCircle( sprite->getContentSize().width/2, MATERIAL_PLAYER);
    body->setCategoryBitmask(BITMASK_BONUS);
    body->setContactTestBitmask(BITMASK_PLAYER);
    sprite->setPhysicsBody(body);

    
}


void KickBonus::activateEffect(Player * player)
{
    player->addKickMultiplier(Definitions::KICKBONUS_MULTIPLIER);
}



void KickBonus::deactivateEffect(Player * player)
{
    player->addKickMultiplier( - Definitions::KICKBONUS_MULTIPLIER );
}

