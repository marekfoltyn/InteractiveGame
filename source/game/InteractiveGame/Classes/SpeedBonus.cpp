#include "SpeedBonus.h"
#include "GameplayDefinitions.h"

SpeedBonus * SpeedBonus::create()
{
    return new SpeedBonus();
}

SpeedBonus::SpeedBonus()
{
    durationMin = SPEEDBONUS_MIN;
    durationMax = SPEEDBONUS_MAX;

    sprite = Sprite::create("bonus_speed.png");
    sprite->setScale(0.5);
    sprite->setName(LABEL_BONUS);
    
    auto body = cocos2d::PhysicsBody::createCircle( sprite->getContentSize().width/2, MATERIAL_PLAYER);
    body->setCategoryBitmask(BITMASK_BONUS);
    body->setContactTestBitmask(BITMASK_PLAYER);
    sprite->setPhysicsBody(body);
}


void SpeedBonus::activateEffect(Player * player)
{
    player->addSpeedMultiplier(SPEEDBONUS_MULTIPLIER);
}



void SpeedBonus::deactivateEffect(Player * player)
{
    player->addSpeedMultiplier( - SPEEDBONUS_MULTIPLIER );
}

