
#ifndef __NETWORKING_TESTS__
#define __NETWORKING_TESTS__

#include "Definitions.h"
#include "BoxFactory.h"
#include "AccelerationMessage.h"
#include "GameState.pb.h"

/**
 * Networking - unit tests
 */

TEST_CASE("Init tests")
{
    SECTION("Definitions")
    {
        // correct ports
        REQUIRE( SERVER_PORT > 0 );
        REQUIRE( SERVER_PORT <= 65525);
        if(SERVER_PORT<49151){
            WARN("SERVER_PORT < 49151, ports may be used by another applications.");
        }
        REQUIRE( CLIENT_PORT > 0 );
        REQUIRE( CLIENT_PORT <= 65525);
        if(CLIENT_PORT<49151){
            WARN("CLIENT_PORT < 49151, ports may be used by another applications.");
        }

        // correctly defined constants
        REQUIRE( MAX_PLAYERS > 0 );
        REQUIRE( RAKNET_SLEEP > 0 );
        REQUIRE( FIND_SERVER_REPEAT_TIME > 0 );
        REQUIRE( SERVER_MENU_LIFETIME > 0 );
        REQUIRE( RECEIVE_TIMEOUT > 0 );
        REQUIRE( TIME_SCENE_TRANSITION > 0 );
        REQUIRE( PORT_RANGE > 0);
        
        // check box id char overflow
        REQUIRE( BOX_ACCELERATION <= 255 );
        REQUIRE( BOX_COLLISION <= 255 );
        REQUIRE( BOX_PLAYER_NAME <= 255 );
        REQUIRE( BOX_KICK <= 255 );
        REQUIRE( BOX_ADMIN <= 255 );
        REQUIRE( BOX_RESET_SCORE <= 255 );
        REQUIRE( BOX_TEAM_SELECT <= 255 );
        REQUIRE( BOX_GAME_STREAM <= 255 );
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
        
        // acceleration
        box = GameNet::BoxFactory::acceleration(0.25, 0.5, 0.75);
        REQUIRE(box->getType() == BOX_ACCELERATION);
        auto msg = GameNet::AccelerationMessage();
        bool res = msg.deserialize(box->getData());
        REQUIRE(res);
        REQUIRE(msg.getX() == 0.25);
        REQUIRE(msg.getY() == 0.5);
        REQUIRE(msg.getZ() == 0.75);
        box->deallocate();
        
        // admin
        GameState state = GameState();
        box = GameNet::BoxFactory::admin(RakNet::UNASSIGNED_SYSTEM_ADDRESS, state);
        REQUIRE(box->getType() == BOX_ADMIN);
        bool reliable = (
            box->getReliability() == PacketReliability::RELIABLE ||
            box->getReliability() == PacketReliability::RELIABLE_ORDERED ||
            box->getReliability() == PacketReliability::RELIABLE_SEQUENCED ||
            box->getReliability() == PacketReliability::RELIABLE_WITH_ACK_RECEIPT ||
            box->getReliability() == PacketReliability::RELIABLE_ORDERED_WITH_ACK_RECEIPT
        );
        REQUIRE(reliable);
        box->deallocate();
        
        // collision
        box = GameNet::BoxFactory::collision(RakNet::UNASSIGNED_SYSTEM_ADDRESS);
        REQUIRE(box->getType() == BOX_COLLISION);
        box->deallocate();

        // kick
        box = GameNet::BoxFactory::kick(10);
        REQUIRE(box->getType() == BOX_KICK);
        REQUIRE(box->getData().compare("10") == 0);
        box->deallocate();

        // kick extreme
        box = GameNet::BoxFactory::kick(256);
        REQUIRE(box->getData().compare("255") == 0);
        box->deallocate();
        
        // player name
        box = GameNet::BoxFactory::playerName("player1");
        REQUIRE(box->getType() == BOX_PLAYER_NAME);
        REQUIRE(box->getData().compare("player1") == 0);
        box->deallocate();
        
        // teamSelection
        box = GameNet::BoxFactory::teamSelection(TEAM_BLUE);
        REQUIRE(box->getType() == BOX_TEAM_SELECT);
        REQUIRE(box->getData().compare(TEAM_BLUE) == 0);
        box->deallocate();
        
        // game stream
        PBGameStream stream = PBGameStream();
        stream.set_width(1000);
        box = GameNet::BoxFactory::gameStream(RakNet::UNASSIGNED_SYSTEM_ADDRESS, stream);
        REQUIRE(box->getType() == BOX_GAME_STREAM);
        PBGameStream str = PBGameStream();
        str.ParseFromString(box->getData());
        REQUIRE(str.width() == 1000);
        box->deallocate();
        
        // game stream reliable
        box = GameNet::BoxFactory::gameStreamReliable(RakNet::UNASSIGNED_SYSTEM_ADDRESS, stream);
        REQUIRE(box->getType() == BOX_GAME_STREAM);
        REQUIRE(box->getReliability() == RELIABLE_ORDERED);
        
    }
    
    SECTION("Connector")
    {
        auto connector = GameNet::Connector::getInstance();
        
        // client
        REQUIRE( connector->startAsClient() == true );
        connector->stop();
        
        // server
        REQUIRE( connector->startAsServer() == true);
        
        // receive()
        auto box = GameNet::Box::create("hello");
        connector->getInterface()->SendLoopback(box->getPacketData(), box->getPacketLength());
        auto received = connector->receive();
        REQUIRE( received->getData().compare("hello") == 0 );
        REQUIRE( connector->receive() == nullptr );
        
        // server name
        connector->setServerName("hello");
        REQUIRE(connector->getServerName().compare("hello") == 0);
        
        connector->stop();
    }
}

#endif // __NETWORKING_TESTS__