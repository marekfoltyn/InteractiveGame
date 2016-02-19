#include <string>

#include "StadiumScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "MessageIdentifiers.h"
#include "Definitions.h"
#include "Connector.h"
#include "Box.h"
#include "BoxFactory.h"
#include "AccelerationMessage.h"

USING_NS_CC;
using namespace GameNet;

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

using namespace cocostudio::timeline;

Scene* StadiumScene::createScene()
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
    
    initServer();
    
    initGUI();
    
    game = Game::getInstance();
    
    //auto rootNode = CSLoader::createNode("MainScene.csb");
    //addChild(rootNode);
    
    return true;
}

void StadiumScene::initServer()
{
    // run async Connector (as a server)
    bool started = Connector::getInstance()->startAsServer(MAX_PLAYERS);
    Connector::getInstance()->setServerName("Mac");
    
    if(!started){
        CCLOG("Server not started!");
        // handle?
        return;
    }
    
    auto callback = CallFunc::create(CC_CALLBACK_0(StadiumScene::processBlock, this));
    auto delay = DelayTime::create(RECEIVE_TIMEOUT);
    auto sequence = Sequence::create(callback, delay, nullptr);
    auto receivePacketAction = RepeatForever::create(sequence);
    this->runAction(receivePacketAction);
}

void StadiumScene::initGUI()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto c = Connector::getInstance();
    
    // background color
    //auto background = cocos2d::LayerColor::create(COLOR_GREEN);
    auto background = Sprite::create("grass.png");
    background->setPosition(Vec2( origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 ));
    this->addChild(background);
    
    // center circle
    auto line = Sprite::create("center.png");
    line->setPosition(Vec2( origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 ));
    this->addChild(line);
 
    float scaleX = visibleSize.width  / 100.0 - 2.0*BORDER/100.0;
    float scaleY = visibleSize.height / 100.0 - 2.0*BORDER/100.0;
    
    // center line
    line = Sprite::create("line.png");
    line->setScaleX(scaleY);
    line->setRotation(90);
    line->setPosition(Vec2( origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
    this->addChild(line);

    
    // top line
    line = Sprite::create("line.png");
    line->setScaleX(scaleX);
    line->setAnchorPoint(Vec2(0,1));
    line->setPosition(Vec2( origin.x + BORDER, origin.y + visibleSize.height - BORDER));
    this->addChild(line);
    
    // bottom line
    line = Sprite::create("line.png");
    line->setScaleX(scaleX);
    line->setAnchorPoint(Vec2(0,0));
    line->setPosition(Vec2( origin.x + BORDER, origin.y + BORDER));
    this->addChild(line);
    
    // left line
    line = Sprite::create("line.png");
    line->setScaleX(scaleY);
    line->setRotation(90);
    line->setAnchorPoint(Vec2(0,0));
    line->setPosition(Vec2( origin.x + BORDER, origin.y + visibleSize.height - BORDER));
    this->addChild(line);
    
    // right line
    line = Sprite::create("line.png");
    line->setScaleX(scaleY);
    line->setRotation(90);
    line->setAnchorPoint(Vec2(0,1));
    line->setPosition(Vec2( origin.x + visibleSize.width - BORDER, origin.y + visibleSize.height - BORDER ));
    this->addChild(line);
    
    scaleX = visibleSize.width/800; // line.jpg is 100px wide
    scaleY *= 0.5;
    
    // left lines near the goal
    line = Sprite::create("line.png");
    line->setScaleX(scaleX);
    line->setAnchorPoint(Vec2(0,1));
    line->setPosition(Vec2( origin.x + BORDER, origin.y + visibleSize.height/2 + scaleY*100/2 ));
    this->addChild(line);
    line = Sprite::create("line.png");
    line->setScaleX(scaleX);
    line->setAnchorPoint(Vec2(0,1));
    line->setPosition(Vec2( origin.x + BORDER, origin.y + visibleSize.height/2 - scaleY*100/2 ));
    this->addChild(line);
    line = Sprite::create("line.png");
    line->setScaleX(scaleY);
    line->setRotation(90);
    line->setAnchorPoint(Vec2(0,1));
    line->setPosition(Vec2( origin.x + BORDER + scaleX*100, origin.y + visibleSize.height/2 + scaleY*100/2 ));
    this->addChild(line);
    
    // right lines near the goal
    line = Sprite::create("line.png");
    line->setScaleX(scaleX);
    line->setAnchorPoint(Vec2(0,1));
    line->setPosition(Vec2( origin.x + visibleSize.width - BORDER - scaleX*100, origin.y + visibleSize.height/2 + scaleY*100/2 ));
    this->addChild(line);
    line = Sprite::create("line.png");
    line->setScaleX(scaleX);
    line->setAnchorPoint(Vec2(0,1));
    line->setPosition(Vec2( origin.x + visibleSize.width - BORDER - scaleX*100, origin.y + visibleSize.height/2 - scaleY*100/2 ));
    this->addChild(line);
    line = Sprite::create("line.png");
    line->setScaleX(scaleY);
    line->setRotation(90);
    line->setAnchorPoint(Vec2(0,0));
    line->setPosition(Vec2( origin.x + visibleSize.width - BORDER - scaleX*100, origin.y + visibleSize.height/2 + scaleY*100/2 ));
    this->addChild(line);
    
    // left goal
    auto goal = Sprite::create("goal.png");
    goal->setScale(SCALE_GOAL);
    goal->setPosition(Vec2( origin.x, origin.y + visibleSize.height/2));
    this->addChild(goal, 2);
    
    // right goal
    goal = Sprite::create("goal.png");
    goal->setRotation(180);
    goal->setScale(SCALE_GOAL);
    goal->setPosition(Vec2( origin.x + visibleSize.width, origin.y + visibleSize.height/2));
    this->addChild(goal, 2);
    
    // goal physics
    // 4 horizontal lines (each goal has two lines - top and down)
    for(int i=0; i<4; i++)
    {
        auto top = Node::create();
        auto body = PhysicsBody::createBox(cocos2d::Size( SCALE_GOAL*goal->getContentSize().width/2, 10), MATERIAL_SOLID);
        body->setDynamic(false);
        body->setCategoryBitmask(BITMASK_SOLID);
        body->setCollisionBitmask(BITMASK_SOLID | BITMASK_BALL | BITMASK_PLAYER);
        body->setContactTestBitmask(BITMASK_SOLID | BITMASK_BALL | BITMASK_PLAYER);
        top->setPhysicsBody(body);
        top->setPosition(Vec2(
                              origin.x + (i>1)*(visibleSize.width) + (1-(i>1)*2)*0.25*SCALE_GOAL*goal->getContentSize().width,
                              origin.y + visibleSize.height/2 + (1 - 2*(i%2)) * SCALE_GOAL*(goal->getContentSize().height/2
        )));
        this->addChild(top);
    }
    // score point detectors
    for(int i=0; i<2; i++)
    {
        auto top = Node::create();
        auto body = PhysicsBody::createBox(cocos2d::Size(
            SCALE_GOAL*goal->getContentSize().width - 2*Sprite::create("ball.png")->getContentSize().width*SCALE_BALL,
            SCALE_GOAL*goal->getContentSize().height - Sprite::create("ball.png")->getContentSize().width*SCALE_BALL));
        body->setDynamic(false);
        body->setCategoryBitmask(BITMASK_SCORE);
        body->setCollisionBitmask(0);
        body->setContactTestBitmask(BITMASK_BALL);
        top->setAnchorPoint(Vec2( i, 0.5 ));
        top->setPhysicsBody(body);
        top->setTag(i); // LEFT and RIGHT (#defined)
        top->setPosition(Vec2(
                              origin.x + (i%2)*(visibleSize.width),
                              origin.y + visibleSize.height/2
        ));
        this->addChild(top);
    }

    
    // physics boundary
    auto edgeBody = PhysicsBody::createEdgeBox(cocos2d::Size(visibleSize.width + 2*BORDER, visibleSize.height + 2*BORDER), MATERIAL_SOLID, BORDER);
    edgeBody->setDynamic(false);
    edgeBody->setCategoryBitmask(BITMASK_SOLID);
    edgeBody->setCollisionBitmask(BITMASK_SOLID | BITMASK_BALL | BITMASK_PLAYER);
    edgeBody->setContactTestBitmask(BITMASK_SOLID | BITMASK_BALL | BITMASK_PLAYER);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Vec2( origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 ));
    edgeNode->setPhysicsBody(edgeBody);
    this->addChild(edgeNode);

    // ball-only physics boundary
    edgeBody = PhysicsBody::createEdgeBox(cocos2d::Size(visibleSize.width, visibleSize.height), MATERIAL_SOLID, BORDER);
    edgeBody->setDynamic(false);
    edgeBody->setCategoryBitmask(BITMASK_BALL_BOUNDARY);
    edgeBody->setCollisionBitmask(BITMASK_BALL);
    edgeBody->setContactTestBitmask(BITMASK_BALL);
    edgeNode = Node::create();
    edgeNode->setPosition(Vec2( origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 ));
    edgeNode->setPhysicsBody(edgeBody);
    this->addChild(edgeNode);
    
    // 4 anti-corner boxes
    for(int i=0; i<4; i++)
    {
        auto box = PhysicsBody::createBox(cocos2d::Size( 90, 90 ));
        box->setDynamic(false);
        box->setCategoryBitmask(BITMASK_BALL_BOUNDARY);
        box->setCollisionBitmask(BITMASK_BALL);
        box->setContactTestBitmask(BITMASK_BALL);
        edgeNode = Node::create();
        edgeNode->setPosition(Vec2( origin.x + (i%2) * visibleSize.width, origin.y + (i>=2) * visibleSize.height ));
        edgeNode->setPhysicsBody(box);
        edgeNode->setRotation(45);
        this->addChild(edgeNode);
    }
    
    // 4 anti corner boxes near goals
    for(int i=0; i<4; i++)
    {
        auto box = PhysicsBody::createBox(cocos2d::Size( 70, 70 ));
        box->setDynamic(false);
        box->setCategoryBitmask(BITMASK_BALL_BOUNDARY);
        box->setCollisionBitmask(BITMASK_BALL);
        box->setContactTestBitmask(BITMASK_BALL);
        edgeNode = Node::create();
        edgeNode->setPosition(Vec2( origin.x + (i%2) * visibleSize.width, origin.y + visibleSize.height/2 + (((i>=2)*2)-1) * goal->getContentSize().height*SCALE_GOAL/2 ));
        edgeNode->setPhysicsBody(box);
        edgeNode->setRotation(45);
        this->addChild(edgeNode);
    }

    
    auto * txtServerName = TextFieldTTF::createWithTTF(c->getServerName(), "Vanilla.ttf", 64);
    txtServerName->setColor(Color3B(54, 72, 99));
    txtServerName->setAnchorPoint(Vec2(0.5, 0.5));
    txtServerName->setPosition(Vec2( origin.x + visibleSize.width/2, origin.y + visibleSize.height - txtServerName->getContentSize().height ));
    //this->addChild(txtServerName);
    
    // score labels
    auto left = Label::createWithTTF("0", "Vanilla.ttf", 100);
    float circle = Sprite::create("center.png")->getContentSize().width/4;
    left->setPosition(Vec2( - circle + origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 ));
    left->setTextColor(COLOR_FONT_TRANSPARENT);
    left->setName(LABEL_SCORE_LEFT);
    this->addChild(left);
    auto right = Label::createWithTTF("0", "Vanilla.ttf", 100);
    right->setPosition(Vec2( circle + origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 ));
    right->setTextColor(COLOR_FONT_TRANSPARENT);
    right->setName(LABEL_SCORE_RIGHT);
    this->addChild(right);

    // leave button
    auto disconnect = Label::createWithTTF("Exit", "Vanilla.ttf", 50);
    disconnect->setAlignment(TextHAlignment::CENTER);
    disconnect->setTextColor(COLOR_FONT_TRANSPARENT);
    auto item = MenuItemLabel::create(disconnect, CC_CALLBACK_1(StadiumScene::btnExitClicked, this));
    item->setAnchorPoint(Vec2(0.5, 1));
    item->setPosition(Vec2( circle + origin.x + visibleSize.width/2, origin.y + visibleSize.height - 2*BORDER ));
    auto menu = Menu::create(item, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
    // ball sprite
    point = Sprite::create("ball.png");
    point->setPosition(Vec2( origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 ));
    point->setScale(SCALE_BALL);
    point->setName(NODE_BALL);
    auto spriteBody = PhysicsBody::createCircle( point->getContentSize().width/2, MATERIAL_BALL );
    spriteBody->setCategoryBitmask(BITMASK_BALL);
    spriteBody->setCollisionBitmask(BITMASK_SOLID | BITMASK_BALL | BITMASK_PLAYER | BITMASK_BALL_BOUNDARY);
    spriteBody->setContactTestBitmask(BITMASK_SOLID | BITMASK_BALL | BITMASK_PLAYER | BITMASK_SCORE | BITMASK_BALL_BOUNDARY);
    spriteBody->setLinearDamping(BALL_DAMPING);
    spriteBody->setAngularDamping(BALL_DAMPING);
    point->setPhysicsBody(spriteBody);
    this->addChild(point);
    prevForce = Vec2(0,0);

    // collision listener
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(StadiumScene::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void StadiumScene::processBlock()
{
    Connector * c = Connector::getInstance();
    Box * box;
    
    // c->receive() returns 0, if no received packet is in the queue
    while( (box = c->receive()) != nullptr )
    {
        switch ( box->getType() )
        {
            case P_PING:
            {
                CCLOG("Client %s has pinged.", box->getAddress().ToString() );
                break;
            }
                
            case P_NEW_CONNECTION:
            {
                CCLOG("%s connected.", box->getAddress().ToString() );
                break;
            }
            case P_CONNECTION_LOST:
            case P_DISCONNECTED:
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
                
                break;
            }
                                
            case P_ACCELERATION:
            {
                onAccelerationBox(box);
                break;
            }
                
            case P_PLAYER_NAME:
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
                
                break;
            }
                
            case P_KICK:
            {
                onPlayerKick(box);
                break;
            }
                
            case P_TACKLE:
            {
                onPlayerTackle(box);
                break;
            }
                
            case P_RESET_SCORE:
            {
                auto left = static_cast<Label*>( this->getChildByName(LABEL_SCORE_LEFT) );
                auto right = static_cast<Label*>( this->getChildByName(LABEL_SCORE_RIGHT) );
                
                left->setString("0");
                right->setString("0");
                
                break;
            }
                
            default:
            {
                CCLOG("Packet type %d was ignored.", box->getType());
                break;
            }
        }
        
        box->deallocate();
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
            
            BoxFactory::collision(player->getAddress())->send();
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



void StadiumScene::onAccelerationBox(Box * box)
{
    int id = RakNet::SystemAddress::ToInteger( box->getAddress() );
    
    auto msg = AccelerationMessage();
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



void StadiumScene::onPlayerKick(Box * box)
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

void StadiumScene::onPlayerTackle(Box * box)
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
    game->end();
}
