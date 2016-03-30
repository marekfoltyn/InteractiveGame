#include "BonusHandler.h"
#include "Game.h"
#include "GameplayDefinitions.h"
#include "KickBonus.h"

#include <string>

USING_NS_CC;

#define SCHEDULE_DISAPPEAR "disappear"
#define BONUS_LIFETIME 15

BonusHandler::BonusHandler()
{
    director = Director::getInstance();
    game = Game::getInstance();
    scene = game->getStadiumManager()->getScene();
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
    // to be refactored (when more bonuses added)
    return KickBonus::create();
}



Vec2 BonusHandler::generatePosition()
{
    auto origin = director->getVisibleOrigin();
    auto visibleSize = director->getVisibleSize();
    
    float x = RandomHelper::random_real<float>(0, visibleSize.width);
    float y = RandomHelper::random_real<float>(0, visibleSize.height);
    
    return Vec2(origin.x + x, origin.y + y);
}