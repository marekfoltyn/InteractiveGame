#include <string>

#include "StadiumScene.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "MessageIdentifiers.h"
#include "Definitions.h"
#include "Connector.h"
#include "Box.h"
#include "BoxFactory.h"
#include "AccelerationMessage.h"

#define COLOR_FONT_TRANSPARENT Color4B(255,255,255,44)

#define NODE_BALL "sprBall"
#define BALL_DAMPING 0.7
#define BORDER 20

#define BITMASK_SOLID            1 // 0000 0001
#define BITMASK_BALL             2 // 0000 0010
#define BITMASK_PLAYER           4 // 0000 0100
#define BITMASK_SCORE            8 // 0000 1000
#define BITMASK_BALL_BOUNDARY   16 // 0001 0000

#define SCALE_GOAL 0.8
#define SCALE_BALL 0.8
#define MATERIAL_SOLID PhysicsMaterial(0.5, 1, 0.5)
#define MATERIAL_BALL PhysicsMaterial(0.5, 0.5, 0.5)

#define LEFT  0
#define RIGHT 1

#define LABEL_SCORE_LEFT "lblScoreLeft"
#define LABEL_SCORE_RIGHT "lblScoreRight"

using namespace cocos2d;

Scene * StadiumScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();

#ifdef DEBUG
    scene->getPhysicsWorld()->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL );
#else
    scene->getPhysicsWorld()->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_NONE );
#endif
    
    scene->getPhysicsWorld()->setGravity(Vec2::ZERO);
    
    // 'layer' is an autorelease object
    auto layer = StadiumScene::create();
    layer->setPhysicsWorld( scene->getPhysicsWorld() );
    layer->setTag(SCENE_TAG);
    
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StadiumScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    initGUI();
    
    //auto rootNode = CSLoader::createNode("MainScene.csb");
    //addChild(rootNode);
    
    return true;
}

void StadiumScene::initGUI()
{

    prevForce = Vec2(0,0);

    // collision listener
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(StadiumScene::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void StadiumScene::addExitHandler( ExitGameHandler * handler )
{
    ExitGameHandler * h = handler;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    float circle = Sprite::create("center.png")->getContentSize().width/4;
    
    // leave button
    auto disconnect = Label::createWithTTF("Exit", "Vanilla.ttf", 50);
    disconnect->setAlignment(TextHAlignment::CENTER);
    disconnect->setTextColor(COLOR_FONT_TRANSPARENT);
    auto item = MenuItemLabel::create(disconnect, [h](cocos2d::Ref* ref){ // [h] captures h variable (and stores?)
        h->execute();
    });
    item->setAnchorPoint(Vec2(0.5, 1));
    item->setPosition(Vec2( circle + origin.x + visibleSize.width/2, origin.y + visibleSize.height - 2*BORDER ));
    auto menu = Menu::create(item, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu,1);

}

void StadiumScene::tempDisconnect(GameNet::Box * box)
{
    CCLOG("%s disconnected.", box->getAddress().ToString());
    
    int id = RakNet::SystemAddress::ToInteger( box->getAddress());
    
    this->removeChild( players[id]->getSprite() );
    
    // set new admin
    if( players[id]->isAdmin() && players.size() >= 2 )
    {
        players.erase(id);
        players.begin()->second->setAsAdmin();
    } else {
        players.erase(id);
    }
    
}

void StadiumScene::tempReset(GameNet::Box * box)
{
    auto left = static_cast<Label*>( this->getChildByName(LABEL_SCORE_LEFT) );
    auto right = static_cast<Label*>( this->getChildByName(LABEL_SCORE_RIGHT) );
    
    left->setString("0");
    right->setString("0");
}

void StadiumScene::tempNewPlayer(GameNet::Box * box)
{
    __String name = box->getData(); // simple string, no need to deserialize
    CCLOG("Player name: %s", name.getCString() );
    
    int id = RakNet::SystemAddress::ToInteger( box->getAddress());
    auto player = Player::create( box->getAddress() );
    players[id] = player;
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    auto sprite = player->getSprite();
    sprite->setTexture("player_no_color.png");
    sprite->setScale(SCALE_BALL);
    sprite->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    auto spriteBody = PhysicsBody::createCircle( sprite->getContentSize().width/2, PhysicsMaterial(0.5, 00, 0.5) );
    spriteBody->setCategoryBitmask(BITMASK_PLAYER);
    spriteBody->setCollisionBitmask(BITMASK_PLAYER | BITMASK_BALL | BITMASK_SOLID);
    spriteBody->setContactTestBitmask(BITMASK_PLAYER | BITMASK_BALL | BITMASK_SOLID);
    spriteBody->setTag(id);
    spriteBody->setRotationEnable(false);
    sprite->setPhysicsBody(spriteBody);
    auto lblName = Label::createWithTTF(name.getCString(), "Vanilla.ttf", sprite->getContentSize().height/2);
    lblName->setPosition(Vec2( sprite->getContentSize().width/2, sprite->getContentSize().height  ));
    lblName->setAnchorPoint(Vec2( 0.5, 0 ));
    lblName->setTextColor(Color4B(255,255,255,44));
    sprite->addChild(lblName,1);
    this->addChild(sprite,1);
    
    // is there an admin?
    if( players.size() == 1 ) // only this new player
    {
        players[id]->setAsAdmin();
    }

}

bool StadiumScene::onContactBegin( cocos2d::PhysicsContact &contact )
{
    PhysicsBody * a[2];
    a[0] = contact.getShapeA()->getBody();
    a[1] = contact.getShapeB()->getBody();

    // player collisions
    for(int i=0; i<2; i++)
    {
        if( a[i]->getCategoryBitmask() & BITMASK_PLAYER ) // it is a player
        {
            int id = a[i]->getTag();
            Player * player = players[id];
            CCLOG("Player %s collided.", player->getAddress().ToString() );
            
            GameNet::BoxFactory::collision(player->getAddress())->send();
        }
    }
    
    // score detection
    for(int i=0; i<2; i++)
    {
        if( a[i]->getCategoryBitmask() & BITMASK_SCORE ) // the ball in the goal
        {
            int goalSide = a[i]->getNode()->getTag();
            CCLOG("GOOAAAALLL to %s", (goalSide==LEFT) ?  "left" : "right" );
            
            // add points
            Label * lbl = static_cast<Label*>( this->getChildByName( (goalSide == LEFT) ? LABEL_SCORE_RIGHT : LABEL_SCORE_LEFT ) );
            int score = __String::create( lbl->getString() )->intValue();
            score++;
            lbl->setString( __String::createWithFormat("%d", score)->getCString() );
        }
    }
    
    return true;
}



void StadiumScene::onAccelerationBox(GameNet::Box * box)
{
    int id = RakNet::SystemAddress::ToInteger( box->getAddress() );
    
    auto msg = GameNet::AccelerationMessage();
    bool res = msg.deserialize(box->getData());
    if(res == false)
    {
        CCLOG("AccelerationMessage deserialization failed.");
        return;
    }
    
    float x = (float) msg.getX();
    float y = (float) msg.getY();
    float forceSize = sqrtf( x*x + y*y );
    
    // coord clean
    if( fabs(x) < 0.08 ) x = 0;
    if( fabs(y) < 0.08 ) y = 0;
    
    if( players.count(id) == 0 )
    {
        // player not found, ignore packet
        CCLOG("player not found, acc packet ignored");
        return;
    }
    auto sprite = players[id]->getSprite();
    
    Vec2 force = Vec2(1000000000*x, 1000000000*y);
    Vec2 prevForce = players[id]->getPreviousForce();
    Vec2 oppositePrevForce = Vec2( - prevForce.x, - prevForce.y );
    players[id]->setAppliedForce(force);
    
    sprite->getPhysicsBody()->applyForce(force);
    sprite->getPhysicsBody()->applyForce(oppositePrevForce);
    sprite->getPhysicsBody()->setVelocityLimit(400*forceSize);
    
    prevForce = force;
}



void StadiumScene::tempKick(GameNet::Box * box)
{
    int id = RakNet::SystemAddress::ToInteger( box->getAddress() );
    auto player = players[id]->getSprite();
    auto ball = this->getChildByName<Sprite *>(NODE_BALL);
    
    float distance = ball->getPosition().distance( player->getPosition() );
    
    // kick to the ball
    if( distance < 2.0/3 * ((player->getContentSize().width * SCALE_BALL + ball->getContentSize().width * SCALE_BALL )) )
    {
        auto direction = ball->getPosition() - player->getPosition();
        direction.normalize();
        int kickForce = 600000;
        auto impulse = direction * kickForce;
        
        ball->getPhysicsBody()->applyImpulse(impulse);
        CCLOG("Ball kick.");
    }
    
}

void StadiumScene::tempTackle(GameNet::Box * box)
{
    int id = RakNet::SystemAddress::ToInteger( box->getAddress() );
    auto player = players[id]->getSprite();
    auto ball = this->getChildByName<Sprite *>(NODE_BALL);
    
    float distance = ball->getPosition().distance( player->getPosition() );
    
    // pass ball
    if( distance < 2.5/3 * ((player->getContentSize().width * SCALE_BALL + ball->getContentSize().width * SCALE_BALL )) )
    {
        auto direction = ball->getPosition() - player->getPosition();
        direction.normalize();
        int kickForce = 300000;
        auto impulse = direction * kickForce;
        //impulse.negate();
        
        ball->getPhysicsBody()->applyImpulse( impulse );
        CCLOG("Ball pass.");
    }
    
}



void StadiumScene::btnExitClicked(Ref * sender)
{
}
