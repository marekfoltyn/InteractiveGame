//
//  Player.cpp
//  InteractiveGame
//
//  Created by Marek Foltýn on 05.02.16.
//
//

#include "Player.h"
#include "BoxFactory.h"
#include "GameplayDefinitions.h"
#include "cocos2d.h"



Player::Player(RakNet::SystemAddress address, std::string name)
{
    this->address = address;
    this->name = name;
    sprite = cocos2d::Sprite::create("player_no_color.png");
    
    auto body = cocos2d::PhysicsBody::createCircle( sprite->getContentSize().width/2, MATERIAL_PLAYER);
    body->setTag( getId() );
    body->setCategoryBitmask(BITMASK_PLAYER);
    body->setContactTestBitmask(BITMASK_ALL);
    body->setCollisionBitmask(PLAYER_COLLIDES_WITH);
    body->setAngularDamping(ANGULAR_DAMPING);
    sprite->setPhysicsBody(body);
    
    // label
    auto lblName = cocos2d::Label::createWithTTF(name.c_str(), "Vanilla.ttf", sprite->getContentSize().height/2);
    lblName->setPosition(cocos2d::Vec2( sprite->getContentSize().width/2, sprite->getContentSize().height/2  ));
    lblName->setAnchorPoint(cocos2d::Vec2( 0.5, -1 ));
    lblName->setTextColor(cocos2d::Color4B(255,255,255,44));
    lblName->setName(LABEL_NAME);
    sprite->addChild(lblName,1);

    admin = false;
    appliedForceVector = cocos2d::Vec2::ZERO;
    realPreviousForce = cocos2d::Vec2::ZERO;
    speedScale = 1;
    kickMultiplier = 1;
    speedMultiplier = 1;
    team = TEAM_AUTO;
    
    // start blinking
    autoBlink();
    
    lblName->schedule([&,lblName](float dt){
        lblName->setRotation( - sprite->getRotation() );
    }, 0.005, "correct");
}

Player * Player::create(std::string name)
{
    return Player::create(RakNet::UNASSIGNED_SYSTEM_ADDRESS, name);
}




Player * Player::create(RakNet::SystemAddress address, std::string name)
{
    Player * player = new Player(address, name);
    return player;
}


int Player::getId()
{
    return RakNet::SystemAddress::ToInteger( getAddress() );
}

void Player::destroy()
{
    delete this;
}



void Player::applyForce(cocos2d::Vec2 forceVector)
{
    appliedForceVector = forceVector;
    float x = forceVector.x;
    float y = forceVector.y;
    
    auto forceSize = forceVector.getLength();
    
    auto force = cocos2d::Vec2(1000000000*x*(getSpeedMultiplier()), 1000000000*y*(getSpeedMultiplier()));
    cocos2d::Vec2 prevForce = realPreviousForce;
    cocos2d::Vec2 oppositePrevForce = cocos2d::Vec2( - prevForce.x, - prevForce.y );
    realPreviousForce = force;
    
    sprite->getPhysicsBody()->applyForce(force);
    sprite->getPhysicsBody()->applyForce(oppositePrevForce);
    sprite->getPhysicsBody()->setVelocityLimit(450*forceSize*(getSpeedScale())*(getSpeedMultiplier()));
}

void Player::setAsAdmin()
{
    admin = true;
    CCLOG("%s is the new admin.", name.c_str());
}

void Player::setSpeedScale(float scale)
{
    if( scale < 0){
        speedScale = 0;
    } else {
        speedScale = scale;
    }
}

void Player::setTeam(std::string newTeam)
{
    if(newTeam == TEAM_RED)
    {
        sprite->setTexture("player_red.png");
    }
    else if(newTeam == TEAM_BLUE)
    {
        sprite->setTexture("player_blue.png");
    }
    team = newTeam;
}



void Player::setKickMultiplier(float multiplier)
{
    kickMultiplier = multiplier;
    if(kickMultiplier < 0) kickMultiplier = 0;
}

void Player::addKickMultiplier(float dt)
{
    kickMultiplier += dt;
    if(kickMultiplier < 0) kickMultiplier = 0;
}



void Player::setSpeedMultiplier(float multiplier)
{
    speedMultiplier = multiplier;
    if(speedMultiplier < 0) speedMultiplier = 0;
}

void Player::addSpeedMultiplier(float dt)
{
    speedMultiplier += dt;
    if(speedMultiplier < 0) speedMultiplier = 0;
}


void Player::blink()
{
    auto blinkfunc = cocos2d::CallFunc::create([&](){
        if(team == TEAM_RED)
        {
            sprite->setTexture("player_red_blink.png");
        }
        else if(team == TEAM_BLUE)
        {
            sprite->setTexture("player_blue_blink.png");
        }
    });

    auto unblinkfunc = cocos2d::CallFunc::create([&](){
        if(team == TEAM_RED)
        {
            sprite->setTexture("player_red.png");
        }
        else if(team == TEAM_BLUE)
        {
            sprite->setTexture("player_blue.png");
        }
    });

    auto delay = cocos2d::DelayTime::create(TIME_BLINK);
    auto sequence = cocos2d::Sequence::create(blinkfunc, delay, unblinkfunc, nullptr);
    sprite->runAction(sequence);
}

void Player::autoBlink()
{
    blink();
    
    // toggle action names - when set to constant, it will run only one
    // because the next schedule will not be called (already scheduled?)
    static unsigned char toggle = 4;
    
    // schedule another blink
    float time = cocos2d::random<float>(2, 8);
    sprite->scheduleOnce([&](float dt){ autoBlink(); },time,cocos2d::__String::createWithFormat("%c", toggle)->getCString());
    
    toggle++;
}
