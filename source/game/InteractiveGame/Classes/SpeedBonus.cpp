#include "SpeedBonus.h"
#include "GameplayDefinitions.h"
#include "Game.h"

SpeedBonus * SpeedBonus::create()
{
    return new SpeedBonus();
}

SpeedBonus::SpeedBonus() : BonusInterface()
{
    name = "SpeedBonus";
    
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


void SpeedBonus::activate(int playerId)
{
    this->playerId = playerId;
    Player * player = game->getPlayer(playerId);
    if(player != nullptr)
    {
        player->addSpeedMultiplier(SPEEDBONUS_MULTIPLIER);
    }
}



void SpeedBonus::deactivate()
{
    this->playerId = playerId;
    Player * player = game->getPlayer(playerId);
    if(player != nullptr)
    {
        player->addSpeedMultiplier( - SPEEDBONUS_MULTIPLIER);
    }
    else
    {
        CCLOG("%s not deactivated - player not found!", name.c_str());
    }
}

