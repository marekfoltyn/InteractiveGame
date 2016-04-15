#include "KickBonus.h"
#include "GameplayDefinitions.h"
#include "Game.h"

KickBonus * KickBonus::create()
{
    return new KickBonus();
}

KickBonus::KickBonus() : BonusInterface()
{
    name = BONUS_KICK;
    
    durationMin = Definitions::TIME_KICKBONUS_MIN;
    durationMax = Definitions::TIME_KICKBONUS_MAX;

    sprite = Sprite::create("bonus_kick.png");
    sprite->setScale(0.5);
    sprite->setName(LABEL_BONUS);
    sprite->setUserData(this);
    
    auto body = cocos2d::PhysicsBody::createCircle( sprite->getContentSize().width/2, MATERIAL_PLAYER);
    body->setCategoryBitmask(BITMASK_BONUS);
    body->setContactTestBitmask(BITMASK_PLAYER | BITMASK_INVISIBLE_PLAYER);
    sprite->setPhysicsBody(body);

    
}


void KickBonus::activate(int playerId)
{
    this->playerId = playerId;
    Player * player = game->getPlayer(playerId);
    if(player != nullptr)
    {
        player->addKickMultiplier(Definitions::KICKBONUS_MULTIPLIER);
    }
}



void KickBonus::deactivate()
{
    Player * player = game->getPlayer(playerId);
    if(player != nullptr)
    {
        player->addKickMultiplier( - Definitions::KICKBONUS_MULTIPLIER );
    }
    else
    {
        CCLOG("%s not deactivated - player not found!", name.c_str());
    }
}

