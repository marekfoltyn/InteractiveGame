#include "LobbyScene.h"

#include "Connector.h"
#include "AccelerationBlok.h"
#include "ServerListScene.h"

USING_NS_CC;

Scene * LobbyScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LobbyScene::create();

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
    
    //auto rootNode = CSLoader::createNode("MainScene.csb");
    //addChild(rootNode);
         
    initGraphics();
    
    auto callback = CallFunc::create(CC_CALLBACK_0(LobbyScene::receiveAllBlocks, this));
    auto delay = DelayTime::create(RECEIVE_TIMEOUT);
    auto sequence = Sequence::create(callback, delay, nullptr);
    auto receivePacketAction = RepeatForever::create(sequence);
    this->runAction(receivePacketAction);

    
    auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(LobbyScene::onAcceleration, this));
    Device::setAccelerometerEnabled(true);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    return true;
}

void LobbyScene::initGraphics(){
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    // background color
    auto background = cocos2d::LayerColor::create(Color4B(54, 72, 99, 255));
    this->addChild(background);
    
    // coordinates
    lblX = Label::createWithTTF("X: ???", "8-Bit-Madness.ttf", visibleSize.height/18);
    lblX->setAnchorPoint(Vec2(0,0));
    lblX->setPosition(Vec2( origin.x, origin.y + 5*lblX->getContentSize().height ));
    this->addChild(lblX);
    
    lblY = Label::createWithTTF("Y: ???", "8-Bit-Madness.ttf", visibleSize.height/18);
    lblY->setAnchorPoint(Vec2(0,0));
    lblY->setPosition(Vec2( origin.x, origin.y + 4*lblX->getContentSize().height ));
    this->addChild(lblY);
    
    lblZ = Label::createWithTTF("Z: ???", "8-Bit-Madness.ttf", visibleSize.height/18);
    lblZ->setAnchorPoint(Vec2(0,0));
    lblZ->setPosition(Vec2( origin.x, origin.y + 3*lblX->getContentSize().height ));
    this->addChild(lblZ);
    
}

void LobbyScene::receiveAllBlocks()
{
    Connector * c = Connector::getInstance();
    Blok * blok;
    
    // c->receive() returns 0, if no received packet is in the queue
    while( (blok = c->receive()) != nullptr )
    {
        switch ( blok->getType() )
        {
            case P_CONNECTION_LOST:
            {
                CCLOG("Connection lost.");
                onConnectionLost(blok);
                break;
            }
                
            default:
            {
                // packet ignored
                CCLOG("Packet %d ignored.", blok->getType() );
                break;
            }
        }
        
        blok->deallocate();
    }
}

void LobbyScene::onConnectionLost(Blok * block)
{
    Scene * main = ServerListScene::createScene();
    Director::getInstance()->replaceScene(main);
}

void LobbyScene::onAcceleration(cocos2d::Acceleration* acc, cocos2d::Event* unused_event)
{
    Blok * blok = AccelerationBlok::Create(acc);
    Connector::getInstance()->send(blok);
    
    lblX->setString( __String::createWithFormat("X: %f", acc->x)->getCString() );
    lblY->setString( __String::createWithFormat("Y: %f", acc->y)->getCString() );
    lblZ->setString( __String::createWithFormat("Z: %f", acc->z)->getCString() );
}

