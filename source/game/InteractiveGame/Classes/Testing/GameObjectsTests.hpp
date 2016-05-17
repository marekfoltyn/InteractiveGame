
#ifndef __GAME_OBJECTS_TESTS__
#define __GAME_OBJECTS_TESTS__

#include "Game.h"
#include "TeamSelectHandler.h"
#include "StartHandler.h"

/**
 * Networking - unit tests
 */

TEST_CASE("Player test")
{
    auto player = Player::create("player");
    
    SECTION("Construction")
    {
        REQUIRE( player->getName().compare("player") == 0 );
        REQUIRE( player->getSprite() != nullptr );
        REQUIRE( player->getSprite()->getPhysicsBody() != nullptr );
    }
    
    SECTION("Behaviour")
    {
        // accelerometer - applying move force
        Vec2 force = Vec2(0.8, 1);
        Vec2 appliedForce;
        
        player->applyForce(force);
        player->getPreviousForceVector();
        player->applyForce(Vec2::ZERO);
        REQUIRE( player->getPreviousForceVector() == Vec2::ZERO );
        
        // admin test
        REQUIRE( player->isAdmin() == false );
        player->setAsAdmin();
        REQUIRE( player->isAdmin() == true );
        
        // speed scale
        player->setSpeedScale(1.25);
        REQUIRE( player->getSpeedScale() == Approx(1.25) );
        player->setSpeedScale(0);
        REQUIRE( player->getSpeedScale() == Approx(0) );
        player->setSpeedScale(-325.56);
        REQUIRE( player->getSpeedScale() == Approx(0) );

        // kick multiplier
        player->setKickMultiplier(1.675);
        REQUIRE( player->getKickMultiplier() == Approx(1.675));
        player->setKickMultiplier(0);
        REQUIRE( player->getKickMultiplier() == Approx(0));
        player->setKickMultiplier(-1235.3);
        REQUIRE( player->getKickMultiplier() == Approx(0));
        player->setKickMultiplier(4.367);
        player->addKickMultiplier(2.5);
        REQUIRE( player->getKickMultiplier() == Approx(6.867));
        player->addKickMultiplier(-50.52356);
        REQUIRE( player->getKickMultiplier() == Approx(0));
        
        // speed multiplier
        player->setSpeedMultiplier(1.675);
        REQUIRE( player->getSpeedMultiplier() == Approx(1.675));
        player->setSpeedMultiplier(0);
        REQUIRE( player->getSpeedMultiplier() == Approx(0));
        player->setSpeedMultiplier(-1235.3);
        REQUIRE( player->getSpeedMultiplier() == Approx(0));
        player->setSpeedMultiplier(4.367);
        player->addSpeedMultiplier(2.5);
        REQUIRE( player->getSpeedMultiplier() == Approx(6.867));
        player->addSpeedMultiplier(-50.52356);
        REQUIRE( player->getSpeedMultiplier() == Approx(0));
        
    }
}

TEST_CASE("Handler test")
{
    SECTION("HandlerMap")
    {
        HandlerMap * map = HandlerMap::create();
        REQUIRE(map != nullptr);
        
        // never-empty test
        int WHATEVER = 123;
        
        REQUIRE_NOTHROW( map->getVoidHandler(WHATEVER)->execute() );
        REQUIRE_NOTHROW( map->getBoxHandler(WHATEVER)->execute(GameNet::Box::create("ahoj")) );
        REQUIRE_NOTHROW( map->getClickHandler(WHATEVER)->execute(nullptr) );
        REQUIRE_NOTHROW( map->getTouchHandler(WHATEVER)->execute(nullptr, cocos2d::ui::Widget::TouchEventType::BEGAN) );
        REQUIRE_NOTHROW( map->getAccHandler(WHATEVER)->execute(new cocos2d::Acceleration(), nullptr) );
        REQUIRE_NOTHROW( map->getStringHandler(WHATEVER)->execute("hello") );
        
        // add, remove
        auto game = Game::getInstance();

        BaseHandler * handler = new StartHandler(game, cocos2d::Director::getInstance());
        map->add(WHATEVER, handler);
        BaseHandler * got = map->getVoidHandler(WHATEVER);
        REQUIRE(got == handler);
        got = map->getBoxHandler(WHATEVER);
        REQUIRE(got != handler);
        delete handler;
        
        handler = new TeamSelectHandler(game);
        map->add(WHATEVER, handler);
        got = map->getBoxHandler(WHATEVER);
        REQUIRE(got == handler);
        got = map->getVoidHandler(WHATEVER);
        REQUIRE(got != handler);
        delete handler;
    }
}

TEST_CASE("Final test")
{
    SECTION("Game exit")
    {
        auto game = Game::getInstance();
        auto connector = GameNet::Connector::getInstance();
        
        game->end();
    }
}

#endif // __GAME_OBJECTS_TESTS__