#include <string>

#include "LobbyScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "MessageIdentifiers.h"
#include "Definitions.h"
#include "Connector.h"
#include "Blok.h"
#include "AccelerationBlok.h"
#include "CollisionBlok.h"
#include "StringBlok.h"

USING_NS_CC;

#define NODE_BALL "sprBall"
#define COLOR_GREEN Color4B(11, 112, 14, 255)
#define BALL_DAMPING 0.6

using namespace cocostudio::timeline;

Scene* LobbyScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_CONTACT );
    scene->getPhysicsWorld()->setGravity(Vec2::ZERO);
    
    // 'layer' is an autorelease object
    auto layer = LobbyScene::create();
    layer->setPhysicsWorld( scene->getPhysicsWorld() );

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LobbyScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    initServer();
    
    initGUI();
    
    CCLOG("P_PING = %d", P_PING);
    CCLOG("P_SERVER_NAME = %d", P_SERVER_NAME);
    
    //auto rootNode = CSLoader::createNode("MainScene.csb");
    //addChild(rootNode);
    
    return true;
}

void LobbyScene::initServer(){
    
    // run async Connector (as a server)
    bool started = Connector::getInstance()->startAsServer(MAX_PLAYERS);
    Connector::getInstance()->setServerName("Mac");
    
    if(!started){
        CCLOG("Server not started!");
        // handle?
        return;
    }
    
    auto callback = CallFunc::create(CC_CALLBACK_0(LobbyScene::processBlock, this));
    auto delay = DelayTime::create(RECEIVE_TIMEOUT);
    auto sequence = Sequence::create(callback, delay, nullptr);
    auto receivePacketAction = RepeatForever::create(sequence);
    this->runAction(receivePacketAction);
    
}

void LobbyScene::initGUI(){
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto c = Connector::getInstance();
    
    // background color
    //auto background = cocos2d::LayerColor::create(Color4B(54, 72, 99, 255));
    auto background = cocos2d::LayerColor::create(COLOR_GREEN);
    this->addChild(background);
    
    // physics boundary
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PhysicsMaterial(0.5, 1, 0.5), 3);
    edgeBody->setDynamic(false);
    edgeBody->setCollisionBitmask(1);
    edgeBody->setContactTestBitmask(true);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Vec2( origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 ));
    edgeNode->setPhysicsBody(edgeBody);
    this->addChild(edgeNode);
    
    
    auto * txtServerName = TextFieldTTF::createWithTTF(c->getServerName(), "Monda-Bold.ttf", 64);
    txtServerName->setColor(Color3B(54, 72, 99));
    txtServerName->setAnchorPoint(Vec2(0.5, 0.5));
    txtServerName->setPosition(Vec2( origin.x + visibleSize.width/2, origin.y + visibleSize.height - txtServerName->getContentSize().height ));
    //this->addChild(txtServerName);
    
    // ball sprite
    point = Sprite::create("ball.png");
    point->setPosition(Vec2( origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 ));
    point->setScale(0.8);
    point->setName(NODE_BALL);
    auto spriteBody = PhysicsBody::createCircle( point->getContentSize().width/2, PhysicsMaterial(0.5, 0.5, 0.5) );
    spriteBody->setCollisionBitmask(1);
    spriteBody->setContactTestBitmask(true);
    spriteBody->setLinearDamping(BALL_DAMPING);
    spriteBody->setAngularDamping(BALL_DAMPING);
    point->setPhysicsBody(spriteBody);
    this->addChild(point);
    prevForce = Vec2(0,0);
    
    // collision listener
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(LobbyScene::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void LobbyScene::processBlock(){
    
    Connector * c = Connector::getInstance();
    Blok * blok;
    
    // c->receive() returns 0, if no received packet is in the queue
    while( (blok = c->receive()) != nullptr )
    {
        switch ( blok->getType() )
        {
            case P_PING:
            {
                CCLOG("Client %s has pinged.", blok->getAddress().ToString() );
                break;
            }
                
            case P_NEW_CONNECTION:
            {
                CCLOG("%s connected.", blok->getAddress().ToString() );
                break;
            }
            case P_CONNECTION_LOST:
            case P_DISCONNECTED:
            {
                CCLOG("%s disconnected.", blok->getAddress().ToString());
                
                int id = RakNet::SystemAddress::ToInteger( blok->getAddress());
                this->removeChild( players[id]->getSprite() );
                players.erase(id);
                
                break;
            }
                                
            case P_ACCELERATION:
            {
                onAccelerationBlok(blok);
                break;
            }
                
            case P_PLAYER_NAME:
            {
                std::string name = StringBlok::parseString(blok);
                CCLOG("Player name: %s", name.c_str() );
                
                int id = RakNet::SystemAddress::ToInteger( blok->getAddress());
                auto player = Player::create( blok->getAddress() );
                players[id] = player;
                
                auto visibleSize = Director::getInstance()->getVisibleSize();
                auto origin = Director::getInstance()->getVisibleOrigin();
                
                auto sprite = player->getSprite();
                sprite->setTexture("player_no_color.png");
                sprite->setScale(0.5);
                sprite->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
                auto spriteBody = PhysicsBody::createCircle( sprite->getContentSize().width/2, PhysicsMaterial(0.5, 00, 0.5) );
                spriteBody->setCollisionBitmask(2);
                spriteBody->setContactTestBitmask(true);
                spriteBody->setTag(id);
                spriteBody->setRotationEnable(false);
                sprite->setPhysicsBody(spriteBody);
                auto lblName = Label::createWithTTF(name, "Monda-Bold.ttf", sprite->getContentSize().height/2);
                lblName->setPosition(Vec2( sprite->getContentSize().width/2, sprite->getContentSize().height  ));
                lblName->setAnchorPoint(Vec2( 0.5, 0 ));
                lblName->setTextColor(Color4B(255,255,255,44));
                sprite->addChild(lblName);
                
                
                this->addChild(sprite);
                break;
            }
                
            case P_KICK:
            {
                onPlayerKick(blok);
                break;
            }
                
            case P_TACKLE:
            {
                onPlayerTackle(blok);
                break;
            }
                
            default:
            {
                CCLOG("Packet type %d was ignored.", blok->getType());
                break;
            }
        }
        
        blok->deallocate();
    }
}

bool LobbyScene::onContactBegin( cocos2d::PhysicsContact &contact )
{
    PhysicsBody * a[2];
    a[0] = contact.getShapeA()->getBody();
    a[1] = contact.getShapeB()->getBody();

    for(int i=0; i<2; i++)
    {
        if( a[i]->getCollisionBitmask() == 2  ) // it is a plaer
        {
            int id = a[i]->getTag();
            Player * player = players[id];
            CCLOG("Player %s collided.", player->getAddress().ToString() );
            auto blok = CollisionBlok::create();
            blok->setAddress( player->getAddress() );
            Connector::getInstance()->send(blok);
        }
    }
    
    return true;
}



void LobbyScene::onAccelerationBlok(Blok * blok)
{
    int id = RakNet::SystemAddress::ToInteger( blok->getAddress() );
    
    auto acc = AccelerationBlok::Parse(blok);
    float x = (float) acc->x;
    float y = (float) acc->y;
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



void LobbyScene::onPlayerKick(Blok * blok)
{
    int id = RakNet::SystemAddress::ToInteger( blok->getAddress() );
    auto player = players[id]->getSprite();
    auto ball = this->getChildByName<Sprite *>(NODE_BALL);
    
    float distance = ball->getPosition().distance( player->getPosition() );
    
    // kick to the ball
    if( distance < player->getContentSize().width * 0.7 )
    {
        auto direction = ball->getPosition() - player->getPosition();
        direction.normalize();
        int kickForce = 600000;
        auto impulse = direction * kickForce;
        
        ball->getPhysicsBody()->applyImpulse(impulse);
        CCLOG("Ball kicked.");
    }
    
}

void LobbyScene::onPlayerTackle(Blok * blok)
{
    int id = RakNet::SystemAddress::ToInteger( blok->getAddress() );
    auto player = players[id]->getSprite();
    auto ball = this->getChildByName<Sprite *>(NODE_BALL);
    
    float distance = ball->getPosition().distance( player->getPosition() );
    
    // kick to the ball
    if( distance < (player->getContentSize().width ) )
    {
        auto direction = ball->getPosition() - player->getPosition();
        direction.normalize();
        int kickForce = 300000;
        auto impulse = direction * kickForce;
        //impulse.negate();
        
        ball->getPhysicsBody()->applyImpulse( impulse );
        CCLOG("Ball kicked.");
    }
    
}















