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

BonusHandler::BonusHandler(Game * game, Director * director)
{
    this->director = director;
    this->game = game;
    stadium = game->getStadium();
    activeBonuses = std::set<BonusInterface *>();
}



void BonusHandler::setBonusDaemonEnabled(bool enabled)
{
    if(!enabled)
    {
        stadium->unschedule(SCHEDULE_GENERATE_BONUS);
        
        // delete existing nodes
        Node * bonus = stadium->getChildByName(LABEL_BONUS);
        while ( bonus != nullptr ) {
            stadium->removeChild(bonus);
            bonus = stadium->getChildByName(LABEL_BONUS);
        }
        
        stadium->getEventDispatcher()->removeEventListener(debugListener);
        
        // deactivate all active bonuses
        // first unschedule deactivation callbacks
        for(auto it=game->players.begin(); it!=game->players.end(); it++)
        {
            it->second->getSprite()->unscheduleAllCallbacks();
        }
        // then deactivate the whole bonuses
        while(activeBonuses.size() > 0)
        {
            deactivate( *(activeBonuses.begin()) );
        }
        
        return;
    }
    
    // repeats every second, but the probability if the bonus will be
    // generated or not depends on PROBABILITY_BONUS
    stadium->schedule([&](float dt)
    {
        probabilityGeneration();
    }
    ,1 , SCHEDULE_GENERATE_BONUS);
    
    // DEBUG - all bonuses generation
    debugListener = EventListenerKeyboard::create();
    debugListener->onKeyPressed = [&](EventKeyboard::KeyCode keyCode, Event* event)
    {
        Vec2 loc = event->getCurrentTarget()->getPosition();
        if( keyCode == EventKeyboard::KeyCode::KEY_B)
        {
            generateDebugBonuses();
        }
    };
    stadium->getEventDispatcher()->addEventListenerWithSceneGraphPriority(debugListener,stadium);
}



void BonusHandler::probabilityGeneration()
{
    float result = RandomHelper::random_real<float>(0, 1);
    if( result > PROBABILITY_BONUS)
    {
        return;
    }

    BonusInterface * bonus = generateBonus();
    auto position = generatePosition();
    
    placeBonus(bonus, position);
}



void BonusHandler::execute(PhysicsBody * first, PhysicsBody * second)
{
    int id = second->getTag();
    auto sprite = dynamic_cast<Sprite*>(first->getNode());
    BonusInterface * bonus = dynamic_cast<BonusInterface*>( (BonusInterface *)sprite->getUserData());
 
    auto player = game->getPlayer(id);
    
    if(bonus == nullptr)
    {
        CCLOG("BonusInterface * not set in bonus sprite!");
        return;
    }

    // activate bonus effect
    for(auto it=activeBonuses.begin(); it!=activeBonuses.end(); it++)
    {
        if( (*it)->getPlayerId()==id && (*it)->getName() == bonus->getName() )
        {
            deactivate(*it);
            
            // schedule name is string-formatted bonus pointer (must be unique)
            player->getSprite()->unschedule(__String::createWithFormat("%p", *it)->getCString());
            break;
        }
    }
    activeBonuses.insert(bonus);
    bonus->activate(id);


    // schedule usual bonus deactivation
    player->getSprite()->scheduleOnce([&, bonus](float dt)
    {
        deactivate(bonus);
    }
    // schedule name is string-formatted bonus pointer (must be unique)
    , bonus->getDuration(), __String::createWithFormat("%p", bonus)->getCString() );
    
    bonus->getSprite()->unschedule(SCHEDULE_DISAPPEAR);
    stadium->removeChild(sprite);
}



void BonusHandler::deactivate(BonusInterface * bonus)
{
    // check if this bonus was not force-deactivated (game over, ...)
    if( activeBonuses.count(bonus) > 0 )
    {
        stadium->unschedule(bonus->getName());
        bonus->deactivate();
        activeBonuses.erase(bonus);
        
        CCLOG("%s effect deactivated.", bonus->getName().c_str());
        delete bonus;
    }
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
    stadium->addChild(bonus->getSprite());
    
    CCLOG("Bonus generated.");
    
    bonus->getSprite()->scheduleOnce([&, bonus](float dt)
    {
        stadium->removeChild(bonus->getSprite());
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