#include "LobbyScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

//#include "MessageIdentifiers.h"
//#include "RakPeerInterface.h"
//#include "Connector.h"
//#include "Definitions.h"

USING_NS_CC;

using namespace cocostudio::timeline;

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
    
    return true;
}

void LobbyScene::initGraphics(){
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    // background
    auto background = Sprite::create("Background.png");
    //background->set( cocos2d::Size( visibleSize.width, visibleSize.height ) );
    background->setPosition(Vec2( origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 ));
    background->setScaleX((visibleSize.width / background->getContentSize().width));
    background->setScaleY((visibleSize.height / background->getContentSize().height));
    this->addChild(background);
    
 
}

