//
//  Player.cpp
//  InteractiveGame
//
//  Created by Marek Foltýn on 05.02.16.
//
//

#include "Player.h"
#include "BoxFactory.h"


Player::Player(RakNet::SystemAddress address)
{
    sprite = cocos2d::Sprite::create();
    this->address = address;
    previousForce = cocos2d::Vec2(0,0);
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



void Player::setAppliedForce(cocos2d::Vec2 force)
{
    previousForce = force;
}

void Player::setAsAdmin()
{
    admin = true;
    auto box = GameNet::BoxFactory::admin( this->getAddress() );
    box->send();
}