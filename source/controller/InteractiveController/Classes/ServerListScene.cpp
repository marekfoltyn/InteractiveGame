#include "ServerListScene.h"
#include "LobbyScene.h"

#include "Connector.h"
#include "ServerNameBlock.h"

USING_NS_CC;

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

bool ServerListScene::init()
{
    // 1. super init first
    if( Layer::init() == false ){
        return false;
    }
    
    initGraphics();
    startReceiveBlocks();
    startFindServers();
        
    return true;
}


void ServerListScene::initGraphics()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    // background
    auto background = cocos2d::LayerColor::create(Color4B(54, 72, 99, 255));
    //auto background = Sprite::create("bg_dummy.png");
    //background->setPosition(Vec2( origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 ));
    this->addChild(background);
    
    // monitor
    auto monitor = Sprite::create("monitor.png");
    monitor->setAnchorPoint(Vec2(0.5, 0.5));
    monitor->setPosition(origin.x + visibleSize.width/2, origin.y + visibleSize.height/2);
    this->addChild(monitor);
    
    // exit button
    auto btnExit = MenuItemImage::create("exit_button.png", "exit_button_pressed.png", CC_CALLBACK_1(ServerListScene::btnLeaveClicked, this));
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


void ServerListScene::startFindServers()
{
    auto step = CallFunc::create(CC_CALLBACK_0(ServerListScene::findServersStep, this));
    auto delay = DelayTime::create(FIND_SERVER_REPEAT_TIME);
    auto sequence = Sequence::create(step, delay, nullptr);
    findServersAction = RepeatForever::create(sequence);
    this->runAction(findServersAction);
}

void ServerListScene::stopFindServers()
{
    this->stopAction(findServersAction);
}

void ServerListScene::startReceiveBlocks()
{
    auto callback = CallFunc::create(CC_CALLBACK_0(ServerListScene::receiveAllBlocks, this));
    auto delay = DelayTime::create(RECEIVE_TIMEOUT);
    auto sequence = Sequence::create(callback, delay, nullptr);
    receivePacketAction = RepeatForever::create(sequence);
    this->runAction(receivePacketAction);
}


void ServerListScene::stopReceiveBlocks()
{
    this->stopAction(receivePacketAction);
}


void ServerListScene::receiveAllBlocks()
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

void ServerListScene::findServersStep(){
    
    Connector::getInstance()->ping();
    decreaseServerLifetimes(); // refresh actually found servers
    
    CCLOG("[ServerListScene] Searching servers...");
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
    
    auto name = __String::create( ServerNameBlock::ServerName(block) );
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
    
    RakNet::SystemAddress address = *(serverMap[tag]->address);
    
    //this->stopAction(searchServersAction);
    //this->stopAction(searchTextLoop);
    //lblSearching->setString("Connecting...");
    
    CCLOG("[ServerListScene] Connecting to %s", address.ToString());
    Connector::getInstance()->connect(address);
    
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

void ServerListScene::onConnected(Block * block){
    
    CCLOG("Connected to %s", block->getAddress().ToString());
    this->stopAction(searchTextLoop);
    lblSearching->setString("Connected.");
    
    //TODO: show lobby scene
    auto scene = LobbyScene::createScene();
    Director::getInstance()->replaceScene(scene);
}

void ServerListScene::btnLeaveClicked(Ref * pSender){
    Connector::getInstance()->stop();
    Director::getInstance()->end();
    exit(0);
}