#include "ServerListScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "MessageIdentifiers.h"
#include "RakPeerInterface.h"
#include "Connector.h"
#include "Definitions.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene * ServerListScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ServerListScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ServerListScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MainScene.csb");

    addChild(rootNode);
    
    auto c = Connector::getInstance();
    c->startClient(44444);
    
    // search for servers every second
    auto foundCallback = CallFunc::create(CC_CALLBACK_0(ServerListScene::findServers, this));
    auto delay = DelayTime::create(FIND_SERVER_REPEAT_TIME);
    auto sequence = Sequence::create(delay, foundCallback, nullptr);
    auto infiniteSearch = RepeatForever::create(sequence);
    this->runAction(infiniteSearch);
    
    CCLOG("Searching for servers");
    c->addPacketCallback(PACKET_SERVER_FOUND, RAKNET_CALLBACK_1(ServerListScene::serverFound, this));
    
    return true;
}

void ServerListScene::findServers(){
    CCLOG("Searching for servers...");
    Connector::getInstance()->FindServers();
}

void ServerListScene::serverFound(RakNet::Packet * p){
    
    char * serverName = (char *) p->data + sizeof(unsigned char) + sizeof(RakNet::TimeMS); // skip message type and response time
    
    CCLOG("%s (%s) in %dms", serverName, p->systemAddress.ToString(), (RakNet::TimeMS) *p->data+1);
    
}