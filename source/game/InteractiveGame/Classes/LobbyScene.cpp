#include <string>

#include "LobbyScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "MessageIdentifiers.h"
#include "Definitions.h"
#include "Connector.h"
#include "Blok.h"
#include "AccelerationBlok.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* LobbyScene::createScene()
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
    Connector::getInstance()->setServerName("InteractiveGame");
    
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
    
    auto * txtServerName = TextFieldTTF::createWithTTF(c->getServerName(), "8-Bit-Madness.ttf", 64);
    txtServerName->setAnchorPoint(Vec2(0.5, 0.5));
    txtServerName->setPosition(Vec2( origin.x + visibleSize.width/2, origin.y + visibleSize.height - txtServerName->getContentSize().height ));
    this->addChild(txtServerName);
    
    point = Sprite::create("exit_button_pressed.png");
    point->setPosition(Vec2( origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 ));
    this->addChild(point);
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
            {
                CCLOG("%s has lost connection.", blok->getAddress().ToString() );
                break;
            }
                
            case P_ACCELERATION:
            {
                onAccelerationBlok(blok);
                break;
            }
                
            default:
            {
                CCLOG("Packet type %c was ignored.", blok->getType());
                break;
            }
        }
        
        blok->deallocate();
    }
}

void LobbyScene::onAccelerationBlok(Blok * blok)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    auto acc = AccelerationBlok::Parse(blok);
    float x = (float) acc->x;
    float y = (float) acc->y;

    point->setPositionX( origin.x + (visibleSize.width/2) + (visibleSize.width/2) * x   );
    point->setPositionY( origin.y + (visibleSize.height/2) + (visibleSize.height/2) * y   );

    
    
}