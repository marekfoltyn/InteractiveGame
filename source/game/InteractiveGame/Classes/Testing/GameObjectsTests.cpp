
#ifndef __GAME_OBJECTS_TESTS__
#define __GAME_OBJECTS_TESTS__

#include "Game.h"

/**
 * Networking - unit tests
 */

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