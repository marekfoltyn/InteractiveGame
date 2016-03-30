#include "InvisibilityBonus.h"
#include "GameplayDefinitions.h"
#include "GameStream.pb.h"
#include "BoxFactory.h"

InvisibilityBonus * InvisibilityBonus::create()
{
    return new InvisibilityBonus();
}

InvisibilityBonus::InvisibilityBonus()
{
    game = Game::getInstance();
    
    durationMin = INVISIBILITY_MIN;
    durationMax = INVISIBILITY_MAX;

    sprite = Sprite::create("bonus_invisibility.png");
    sprite->setScale(0.5);
    sprite->setName(LABEL_BONUS);
    
    auto body = cocos2d::PhysicsBody::createCircle( sprite->getContentSize().width/2, MATERIAL_PLAYER);
    body->setCategoryBitmask(BITMASK_BONUS);
    body->setContactTestBitmask(BITMASK_PLAYER);
    sprite->setPhysicsBody(body);
}


void InvisibilityBonus::activateEffect(Player * player)
{
    // hide player (physics body works normally)
    player->getSprite()->setVisible(false);
    
    // send initial data - pitch ratio, players, and so on...
    sendInitialGameStream(player);
    player->getSprite()->schedule([&, player](float dt)
    {
        sendGameStreamDelta(player);
    },
    TIME_GAMESTREAM_DELAY, SCHEDULE_GAMESTREAM);
}



void InvisibilityBonus::deactivateEffect(Player * player)
{
    player->getSprite()->setVisible(true);
    player->getSprite()->unschedule(SCHEDULE_GAMESTREAM);
    sendLastGameStream(player);
}



void InvisibilityBonus::sendInitialGameStream(Player * player)
{
    PBGameStream stream;
    double ratio = game->getStadiumRatio();
    
    stream.set_active(true);
    stream.set_pitchratio(ratio);
    
    GameNet::BoxFactory::gameStream(player->getAddress(), stream)->send();
}



void InvisibilityBonus::sendGameStreamDelta(Player * player)
{
    
}



void InvisibilityBonus::sendLastGameStream(Player * player)
{
    PBGameStream stream;
    stream.set_active(false);
    
    GameNet::BoxFactory::gameStream(player->getAddress(), stream)->send();
    
}