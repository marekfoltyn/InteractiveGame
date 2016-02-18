//
//  Player.cpp
//  InteractiveGame
//
//  Created by Marek Foltýn on 05.02.16.
//
//

#include "Player.h"
#include "BoxFactory.h"

using namespace GameNet;


Player::Player(RakNet::SystemAddress address)
{
    sprite = Sprite::create();
    this->address = address;
    previousForce = Vec2(0,0);
}



Player * Player::create(RakNet::SystemAddress address)
{
    Player * player = new Player(address);
    return player;
}



void Player::destroy()
{
    delete this;
}



void Player::setAppliedForce(Vec2 force)
{
    previousForce = force;
}

void Player::setAsAdmin()
{
    admin = true;
    auto box = BoxFactory::admin( this->getAddress() );
    box->send();
}