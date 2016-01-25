#include "ServerListScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"

#include "MessageIdentifiers.h"
#include "RakPeerInterface.h"

#include "Block.h"
#include "BlockParser.h"
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
    startPacketAction();
    startPing();
    
    // start accelerometer
    auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(ServerListScene::onAcceleration, this));
    Device::setAccelerometerEnabled(true);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
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
    
    // coordinates
    lblX = Label::createWithTTF("X: ???", "8-Bit-Madness.ttf", visibleSize.height/18);
    lblX->setAnchorPoint(Vec2(0,0));
    lblX->setPosition(Vec2( origin.x + visibleSize.width/2 -160, origin.y + 3*lblX->getContentSize().height ));
    this->addChild(lblX);

    lblY = Label::createWithTTF("Y: ???", "8-Bit-Madness.ttf", visibleSize.height/18);
    lblY->setAnchorPoint(Vec2(0,0));
    lblY->setPosition(Vec2( origin.x + visibleSize.width/2 -160, origin.y + 2*lblX->getContentSize().height ));
    this->addChild(lblY);
    
    lblZ = Label::createWithTTF("Z: ???", "8-Bit-Madness.ttf", visibleSize.height/18);
    lblZ->setAnchorPoint(Vec2(0,0));
    lblZ->setPosition(Vec2( origin.x + visibleSize.width/2 -160, origin.y + 1*lblX->getContentSize().height ));
    this->addChild(lblZ);

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
            CCLOG("%s removed for inactivity.",i->second->address->ToString());
            
            //TODO: delete menu entry
            //auto label = (MenuItemLabel *) serverMenu->getChildByTag( (int) RakNet::SystemAddress::ToInteger( * (i->second->address) ));
            //serverMenu->removeChild(label, true);
            
            serverMap.erase(i->first);
            
            // if missing this, when only one server, app breaks (iterator is behind the end)
            if( serverMap.size() == 0 || i == serverMap.end() ){
                return;
            }
        }
        
    }
    
}

void ServerListScene::serverFound(Block * block){
    
    auto name = __String::create( BlockParser::ServerName(block) );
    CCLOG("Server response: %s", name->getCString() );
    
    /*if(lblServerName != nullptr){
        lblServerName->setString(name->getCString());
    }*/
    
    addOrUpdateServer(name, block->getAddress());
}

void ServerListScene::btnServerClicked(Ref * pSender){

    int tag = ((cocos2d::MenuItemLabel *) pSender)->getTag();

    if(tag == -1)
    {
        CCLOG("Tag not found. Can't connect.");
        return;
    }
    
    RakNet::SystemAddress * address = serverMap[tag]->address;
    
    //this->stopAction(searchServersAction);
    //this->stopAction(searchTextLoop);
    //lblSearching->setString("Connecting...");
    
    Connector::getInstance()->connect(*address);
    
}

void ServerListScene::addOrUpdateServer(cocos2d::__String * serverName, RakNet::SystemAddress address){

    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    int hash = (int) RakNet::SystemAddress::ToInteger( address );
    
    if( serverMap.count( hash ) == 0 ){

        // create new entry
        ServerMapEntry * s = new ServerMapEntry();
        s->inactiveSeconds = 0;
        s->address = new RakNet::SystemAddress(address); // copy adress (packet will be deallocated)
        
        serverMap[hash] = s;
        CCLOG("%s added (hash: %d).", serverName->getCString(), hash);
        
        std::string name(serverName->getCString());
        
        auto label = Label::createWithTTF(name, "8-Bit-Madness.ttf", visibleSize.height/12);
        
        auto item = MenuItemLabel::create(label, CC_CALLBACK_1(ServerListScene::btnServerClicked, this));
        item->setPosition(Vec2( origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 ));
        item->setTag(hash); // SystemAddress will be found by tag (in hashmap)
        
        auto menu = Menu::create(item, NULL);
        menu->setPosition(Vec2::ZERO);
        this->addChild(menu);
        
        
    } else {
        // server already exists - refresh server lifetime
        auto s = serverMap[hash];
        s->inactiveSeconds = 0;
    }
    
}

void ServerListScene::startPacketAction()
{
    auto callback = CallFunc::create(CC_CALLBACK_0(ServerListScene::packetAction, this));
    auto delay = DelayTime::create(RECEIVE_TIMEOUT);
    auto sequence = Sequence::create(callback, delay, nullptr);
    receivePacketAction = RepeatForever::create(sequence);
    this->runAction(receivePacketAction);
}


void ServerListScene::stopPacketAction()
{
    this->stopAction(receivePacketAction);
}


void ServerListScene::packetAction()
{
    Connector * c = Connector::getInstance();
    Block * block;
    
    // c->receive() returns 0, if no received packet is in the queue
    while( (block = c->receive()) != nullptr )
    {
        switch ( block->getType() )
        {
            case P_SERVER_NAME:
            {
                serverFound(block);
                break;
            }
                
            case P_CONNECTED:
            {
                onConnected(block);
                break;
            }
            
            default:
            {
                // packet ignored
                break;
            }
        }
        
        block->deallocate();
    }
    
    
}

void ServerListScene::onAcceleration(Acceleration* acc, Event* unused_event){
    auto x = __String::createWithFormat("X: %f", acc->x);
    auto y = __String::createWithFormat("Y: %f", acc->y);
    auto z = __String::createWithFormat("Z: %f", acc->z);
    lblX->setString(x->getCString());
    lblY->setString(y->getCString());
    lblZ->setString(z->getCString());
}

void ServerListScene::onConnected(Block * block){
    
    CCLOG("Connected to %s", block->getAddress().ToString());
    this->stopAction(searchTextLoop);
    this->stopAction(searchServersAction);
    lblSearching->setString("Connected.");
    
    //TODO: show lobby scene
}

void ServerListScene::exitGame(Ref * pSender){
    //Connector::getInstance()->stop();
    Director::getInstance()->end();
    exit(0);
}