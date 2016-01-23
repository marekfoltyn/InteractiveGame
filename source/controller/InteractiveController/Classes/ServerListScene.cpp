#include "ServerListScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "MessageIdentifiers.h"
#include "RakPeerInterface.h"
#include "Connector.h"
#include "Definitions.h"

#include <map>

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
    // 1. super init first
    if( Layer::init() == false ){
        return false;
    }
    
    initGraphics();
    startPing();
    
    return true;
}


void ServerListScene::initGraphics(){
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    // background
    auto background = Sprite::create("Background.png");
    //background->set( cocos2d::Size( visibleSize.width, visibleSize.height ) );
    background->setPosition(Vec2( origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 ));
    background->setScaleX((visibleSize.width / background->getContentSize().width));
    background->setScaleY((visibleSize.height / background->getContentSize().height));
    this->addChild(background);
    
    // monitor
    auto monitor = Sprite::create("monitor.png");
    monitor->setAnchorPoint(Vec2(0.5, 0.5));
    monitor->setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);
    this->addChild(monitor);
    
    // exit button
    auto btnExit = MenuItemImage::create("exit_button.png", "exit_button_pressed.png", CC_CALLBACK_1(ServerListScene::exitGame, this));
    btnExit->setScale(2);
    btnExit->setPosition( origin.x + visibleSize.height + 7*(visibleSize.width - visibleSize.height)/8 - btnExit->getContentSize().width, origin.y + visibleSize.height - btnExit->getContentSize().height );
    //this->addChild(btnExit); // no, because it will be part of menu
    
    // menu
    menu = Menu::create(btnExit, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
    // Searching for servers... label
    lblSearching = Label::createWithTTF("", "8-Bit-Madness.ttf", visibleSize.height/12);
    lblSearching->setAnchorPoint(Vec2(0,1));
    lblSearching->setPosition(Vec2(origin.x + visibleSize.width/2 - 160, origin.y + visibleSize.height - 20));
    this->addChild(lblSearching);
    // dots changing
    auto delay = DelayTime::create(0.5);
    auto sequence = Sequence::create(
                                     CallFunc::create(CC_CALLBACK_0(ServerListScene::searchLabelNoDot,this)),
                                     delay,
                                     CallFunc::create(CC_CALLBACK_0(ServerListScene::searchLabelOneDot,this)),
                                     delay->clone(),
                                     CallFunc::create(CC_CALLBACK_0(ServerListScene::searchLabelTwoDots,this)),
                                     delay->clone(),
                                     CallFunc::create(CC_CALLBACK_0(ServerListScene::searchLabelThreeDots,this)),
                                     delay->clone(),
                                     nullptr );
    searchTextLoop = RepeatForever::create(sequence);
    this->runAction(searchTextLoop);
    
    // Server names menu
    /*serversView = ui::ScrollView::create();
     serversView->setDirection( ui::ScrollView::Direction::VERTICAL );
     serversView->setContentSize( cocos2d::Size(visibleSize.height, visibleSize.height) );
     serversView->setInnerContainerSize( cocos2d::Size(visibleSize.height, visibleSize.height) );
     serversView->setPosition(Vec2(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2));
     serversView->setAnchorPoint(Vec2(0.5, 0.5));
     serversView->setBounceEnabled(true);*/
    
    //serversView->addChild(serverMenu);
    //this->addChild(serversView);
    
    
    /*    auto label = Label::createWithTTF("Ahojky", "8-Bit-Madness.ttf", visibleSize.height/12);
     //auto item = MenuItemFont::create(name, CC_CALLBACK_1(ServerListScene::btnServerClicked, this));
     auto item = MenuItemLabel::create(label, CC_CALLBACK_1(ServerListScene::btnServerClicked, this));
     item->setPosition(Vec2( origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 ));
     
     auto menu = Menu::create(item, NULL);
     menu->setPosition(Vec2::ZERO);
     this->addChild(menu);*/
    
}


void ServerListScene::startPing(){
    
    auto findCallback = CallFunc::create(CC_CALLBACK_0(ServerListScene::findServers, this));
    auto delay = DelayTime::create(FIND_SERVER_REPEAT_TIME);
    auto sequence = Sequence::create(findCallback, delay, nullptr);
    searchServersAction = RepeatForever::create(sequence);
    this->runAction(searchServersAction);
}

void ServerListScene::stopPing(){
    
    this->stopAction(searchServersAction);
}


void ServerListScene::searchLabelNoDot(){
    lblSearching->setString("Searching servers");
}
void ServerListScene::searchLabelOneDot(){
    lblSearching->setString("Searching servers.");
}
void ServerListScene::searchLabelTwoDots(){
    lblSearching->setString("Searching servers..");
}
void ServerListScene::searchLabelThreeDots(){
    lblSearching->setString("Searching servers...");
}


void ServerListScene::findServers(){
    
    Connector::getInstance()->ping();
    decreaseServerLifetimes(); // refresh actually found servers
    
    CCLOG("Searching for servers...");
}

void ServerListScene::decreaseServerLifetimes(){
    
    for(std::map<int, ServerMapEntry*>::iterator i = serverMap.begin(); i != serverMap.end(); i++) {
        // iterator->first = key
        // iterator->second = value

        i->second->inactiveSeconds++;
        
        CCLOG("%s lifetime set to %d", i->second->address->ToString(), (int) i->second->inactiveSeconds);
        
        if( i->second->inactiveSeconds >= SERVER_MENU_LIFETIME){

            //delete
            //CCLOG("%s removed for inactivity.",i->second->address->ToString());
            
            //TODO: delete menu entry
            //auto label = (MenuItemLabel *) serverMenu->getChildByTag( (int) RakNet::SystemAddress::ToInteger( * (i->second->address) ));
            //serverMenu->removeChild(label, true);
            //serverMap.erase(i->first);
            
            // if missing this, when only one server, app breaks
            if( serverMap.size() == 0 || i == serverMap.end() ){
                return;
            }
        }
        
    }
    
}

void ServerListScene::serverFound(RakNet::Packet * p){
    
    int overhead = sizeof(unsigned char) + sizeof(RakNet::TimeMS);
    const char * serverNameInPacket = (char *) p->data + overhead; // skip message type and response time
    auto name = __String::create(serverNameInPacket);
    
    /*if(lblServerName != nullptr){
        lblServerName->setString(name->getCString());
    }*/
    
    addOrUpdateServer(name, &p->systemAddress);
    
    CCLOG("%s (%s) in %dms", name->getCString(), p->systemAddress.ToString(), (RakNet::TimeMS) *p->data+1);
}

void ServerListScene::btnServerClicked(Ref * pSender){
    
    CCLOG("Connecting...");
    //Connector::getInstance()->connect(p->systemAddress);
    
}

void ServerListScene::addOrUpdateServer(cocos2d::__String * serverName, RakNet::SystemAddress * address){

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    int hash = (int) RakNet::SystemAddress::ToInteger( *address );
    
    if( serverMap.count( hash ) == 0 ){

        // create new entry
        ServerMapEntry * s = new ServerMapEntry();
        s->inactiveSeconds = 0;
        s->address = new RakNet::SystemAddress(*address); // copy adress (packet will be deallocated)
        
        serverMap[hash] = s;
        CCLOG("%s added.", serverName->getCString());
        
        /*std::string name(serverName->getCString());
        int tag = (int) RakNet::SystemAddress::ToInteger( *address );
        
        auto label = Label::createWithTTF(name, "8-Bit-Madness.ttf", visibleSize.height/12);
        //auto item = MenuItemFont::create(name, CC_CALLBACK_1(ServerListScene::btnServerClicked, this));
        auto item = MenuItemLabel::create(label, CC_CALLBACK_1(ServerListScene::btnServerClicked, this));
        item->setPosition(Vec2( origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 ));
        
        auto menu = Menu::create(item, NULL);
        menu->setPosition(Vec2( origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 ));
        this->addChild(menu);*/
        
        
        auto label = Label::createWithTTF("Ahojky", "8-Bit-Madness.ttf", visibleSize.height/12);
        //auto item = MenuItemFont::create(name, CC_CALLBACK_1(ServerListScene::btnServerClicked, this));
        auto item = MenuItemLabel::create(label, CC_CALLBACK_1(ServerListScene::btnServerClicked, this));
        item->setPosition(Vec2( origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 ));
        
        auto menu = Menu::create(item, NULL);
        menu->setPosition(Vec2::ZERO);
        this->addChild(menu);
        
        
    } else {
        // server already exists - refresh server lifetime
        auto s = serverMap[hash];
        s->inactiveSeconds = 0;
    }
    
}

void ServerListScene::onConnected(RakNet::Packet * p){
    CCLOG("Connected to %s", p->systemAddress.ToString());
    this->stopAction(searchServersAction);
    this->stopAction(searchTextLoop);
    
    lblSearching->setString("Connected.");
    
    //TODO: show lobby scene
}

void ServerListScene::exitGame(Ref * pSender){
    Connector::getInstance()->stop();
    Director::getInstance()->end();
    exit(0);
}