
#ifndef __NETWORKING_TESTS__
#define __NETWORKING_TESTS__

#include "Definitions.h"
#include "BoxFactory.h"

/**
 * Networking - unit tests
 */

TEST_CASE("Init tests"){
    SECTION("Definitions"){
    
        // correct ports
        REQUIRE( SERVER_PORT > 0 );
        REQUIRE( SERVER_PORT <= 65525);
        if(SERVER_PORT<49151){
            WARN("SERVER_PORT < 49151, port may be registered by another application.");
        }
        REQUIRE( CLIENT_PORT > 0 );
        REQUIRE( CLIENT_PORT <= 65525);
        if(CLIENT_PORT<49151){
            WARN("CLIENT_PORT < 49151, port may be registered by another application.");
        }

        // correctly defined constants
        REQUIRE( MAX_PLAYERS > 0 );
        REQUIRE( RAKNET_SLEEP > 0 );
        REQUIRE( FIND_SERVER_REPEAT_TIME > 0 );
        REQUIRE( SERVER_MENU_LIFETIME > 0 );
        REQUIRE( RECEIVE_TIMEOUT > 0 );
        REQUIRE( TIME_SCENE_TRANSITION > 0 );
        
    }
}

TEST_CASE("GameNet tests")
{
    SECTION("Box")
    {
        GameNet::Box * box = nullptr;
        
        // string to box
        box = GameNet::Box::create("test");
        REQUIRE( box->getData().compare("test") == 0 );
        box->deallocate();
        
        // packet to box
        RakNet::Packet * packet = new RakNet::Packet();
        packet->data = new unsigned char[5];
        packet->length = 5;
        memcpy(packet->data, "\0test", 5*sizeof(char));
        box = GameNet::Box::create(packet);
        REQUIRE( box->getData().compare("test") == 0 );
        delete [] box->getPacketData();
        delete [] packet->data;
        delete box;
    }
    
    SECTION("Box Factory")
    {
        GameNet::Box * box;

        // kick
        box = GameNet::BoxFactory::kick(10);
        REQUIRE( box->getData().compare("10") == 0 );
        box->deallocate();

        // kick extreme
        box = GameNet::BoxFactory::kick(256);
        REQUIRE( box->getData().compare("255") == 0 );
        box->deallocate();
        
    }
    
    SECTION("Connector")
    {
        auto connector = GameNet::Connector::getInstance();
        
        // client
        REQUIRE( connector->start() == true );
        connector->stop();
        
        // server
        REQUIRE( connector->startAsServer() == true);
        
        // receive()
        auto box = GameNet::Box::create("hello");
        connector->getInterface()->SendLoopback(box->getPacketData(), box->getPacketLength());
        auto received = connector->receive();
        REQUIRE( received->getData().compare("hello") == 0 );
        REQUIRE( connector->receive() == nullptr );
        
    }
}

#endif // __NETWORKING_TESTS__