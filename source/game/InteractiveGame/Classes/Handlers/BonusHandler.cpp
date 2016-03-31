#include "BonusHandler.h"
#include "Game.h"
#include "GameplayDefinitions.h"
#include "KickBonus.h"
#include "SpeedBonus.h"
#include "InvisibilityBonus.h"

#include <string>

USING_NS_CC;

#define SCHEDULE_DISAPPEAR "disappear"
#define BONUS_LIFETIME 15

BonusHandler::BonusHandler()
{
    director = Director::getInstance();
    game = Game::getInstance();
    scene = game->getStadium();
}



void BonusHandler::execute()
{
    float result = RandomHelper::random_real<float>(0, 1);
    if( result > PROBABILITY_BONUS)
    {
        return;
    }

    // let's generate a bonus!
    
    BonusInterface * bonus = generateBonus();
    auto position = generatePosition();
    
    placeBonus(bonus, position);
}



void BonusHandler::execute(PhysicsBody * first, PhysicsBody * second)
{
    int id = second->getTag();
    auto player = game->getPlayer(id);
    auto sprite = dynamic_cast<Sprite*>(first->getNode());
    auto bonus = (BonusInterface*) sprite->getUserData();

    bonus->activate(player);
    scene->removeChild(sprite);
}



BonusInterface * BonusHandler::generateBonus()
{
    auto random = RandomHelper::random_int(0, 2);
    
    // to be refactored (when more bonuses added)
    if( random == 0 ){
        return SpeedBonus::create();
    } else if ( random == 1 ) {
        return KickBonus::create();
    } else {
        return InvisibilityBonus::create();
    }
}



void BonusHandler::placeBonus(BonusInterface * bonus, Vec2 position)
{
    bonus->getSprite()->setPosition( position );
    // connect Sprite with the bonus
    bonus->getSprite()->setUserData(bonus);
    scene->addChild(bonus->getSprite());
    
    CCLOG("Bonus generated.");
    
    bonus->getSprite()->scheduleOnce([&, bonus](float dt)
    {
        scene->removeChild(bonus->getSprite());
        delete bonus;
        CCLOG("Bonus removed.");
    },
    BONUS_LIFETIME, SCHEDULE_DISAPPEAR);
}



Vec2 BonusHandler::generatePosition()
{
    auto origin = director->getVisibleOrigin();
    auto visibleSize = director->getVisibleSize();
    
    float x = RandomHelper::random_real<float>(0, visibleSize.width);
    float y = RandomHelper::random_real<float>(0, visibleSize.height);
    
    return Vec2(origin.x + x, origin.y + y);
}



void BonusHandler::generateDebugBonuses()
{
    auto origin = director->getVisibleOrigin();
    auto visibleSize = director->getVisibleSize();
    auto offset = Vec2(100,0);
    auto position = Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height - 5*BORDER);
    position -= 4 * offset;

    for(int i=0; i<3; i++)
    {
        placeBonus(KickBonus::create(), position + i * offset);
        placeBonus(SpeedBonus::create(), position + (i+3) * offset);
        placeBonus(InvisibilityBonus::create(), position + (i+6) * offset);
    }
}