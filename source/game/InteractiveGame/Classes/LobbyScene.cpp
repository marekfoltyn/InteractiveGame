#include <string>

#include "LobbyScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "MessageIdentifiers.h"
#include "Definitions.h"
#include "Connector.h"

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
    
    //auto rootNode = CSLoader::createNode("MainScene.csb");
    //addChild(rootNode);
    
    return true;
}

void LobbyScene::initServer(){
    
    // run async Connector (as a server)
    bool started = Connector::getInstance()->startAsServer(MAX_PLAYERS);
    
    if(!started){
        CCLOG("Server not started!");
        // handle?
        return;
    }
    
    Connector::getInstance()->setServerName("InteractiveGame");
    
}

void LobbyScene::initGUI(){
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    auto c = Connector::getInstance();
    
    auto * txtServerName = TextFieldTTF::createWithTTF(c->getServerName(), "8-Bit-Madness.ttf", 64);
    txtServerName->setAnchorPoint(Vec2(0.5, 0.5));
    txtServerName->setPosition(Vec2( origin.x + visibleSize.width/2, origin.y + visibleSize.height - txtServerName->getContentSize().height ));
    
    this->addChild(txtServerName);
    
    addPacketCallbacks();
}

void LobbyScene::addPacketCallbacks(){
    
    //auto c = Connector::getInstance();

    //c->addPacketCallback(P_NEW_INCOMING_CONNECTION, RAKNET_CALLBACK_1(LobbyScene::onNewConnection, this));
    
}

void LobbyScene::onNewConnection(RakNet::Packet * p){
    
    LOG("%s connected.\n", p->systemAddress.ToString());
    
}