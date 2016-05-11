
#ifndef __GAME_OBJECTS_TESTS__
#define __GAME_OBJECTS_TESTS__

/**
 * Handlers - unit tests
 */


TEST_CASE("Final test")
{
    SECTION("Game exit")
    {
        GameNet::Connector::getInstance()->stop();
        Director::getInstance()->end();
    }
}


#endif // __GAME_OBJECTS_TESTS__