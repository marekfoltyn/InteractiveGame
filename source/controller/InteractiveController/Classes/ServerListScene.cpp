#include "ServerListScene.h"
#include "LobbyScene.h"

#include "Connector.h"
#include "ServerNameBlok.h"

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
    
    // background color
    auto background = cocos2d::LayerColor::create(Color4B(54, 72, 99, 255));
    this->addChild(background);
    
    // background top triangle
    auto top = Sprite::create("bg_triangle_top.png");
    float scaleWidth = (0.6 * visibleSize.width) / top->getContentSize().width; // top triangle will have width 60% of the screen width
    float scaleHeight = (1.0/12) * visibleSize.height / top->getContentSize().height; // 1/12 of the visible height
    top->setScale(scaleWidth, scaleHeight);
    top->setAnchorPoint(Vec2(0,1));
    top->setPosition(Vec2( origin.x, origin.y + visibleSize.height ));
    this->addChild(top);
    
    // background bottom triangle
    auto bottom = Sprite::create("bg_triangle_top.png");
    bottom->setScale(scaleWidth, scaleHeight);
    bottom->setAnchorPoint(Vec2(0,1));
    bottom->setRotation(180);
    bottom->setPosition(Vec2( origin.x + visibleSize.width, origin.y));
    this->addChild(bottom);
    
    // exit button
    auto btnExit = MenuItemImage::create("exit.png", "exit_clicked.png", CC_CALLBACK_1(ServerListScene::btnLeaveClicked, this));
    btnExit->setPosition( origin.x + visibleSize.width/2 + 455, origin.y + visibleSize.height - 308 );
    btnExit->setRotation(15);
    //this->addChild(btnExit); // no, because it will be part of menu
    
    // about button
    auto btnAbout = MenuItemImage::create("about.png", "about_clicked.png" /*, CC_CALLBACK_1(ServerListScene::btnLeaveClicked, this)*/ );
    btnAbout->setPosition( origin.x + visibleSize.width/2 + 485, origin.y + visibleSize.height - 183 );
    btnAbout->setRotation(-15);

    // help button
    auto btnHelp = MenuItemImage::create("help.png", "help_clicked.png" /*, CC_CALLBACK_1(ServerListScene::btnLeaveClicked, this)*/ );
    btnHelp->setPosition( origin.x + visibleSize.width/2 + 385, origin.y + visibleSize.height - 413 );
    btnHelp->setRotation(41);
    
    // game logo
    auto logo = MenuItemImage::create("logo.png", "logo.png");
    logo->setPosition(Vec2( origin.x + visibleSize.width/2 + 210, origin.y + visibleSize.height - 257 ));
    //this->addChild(logo);
    
    // player name background
    //auto nameBackground = Sprite::create("name_bg.png");
    //nameBackground->setPosition(Vec2( origin.x + visibleSize.width/2 - 265, origin.y + visibleSize.height - 257 ));
    //this->addChild(nameBackground);
    
    // background behind text field
    auto bgName = ui::ImageView::create("name_bg.png");
    bgName->setPosition(Vec2( origin.x + visibleSize.width/2 - 265, origin.y + visibleSize.height - 257 ));
    this->addChild(bgName);
    
    // player name - text field
    auto txtName = ui::TextField::create("<player name>", "Monda-Bold.ttf", 80);
    txtName->setMaxLength(12);
    txtName->setMaxLengthEnabled(true);
    txtName->setAnchorPoint(Vec2(0,0));
    txtName->setPosition(Vec2( origin.x + visibleSize.width/2 - 635, origin.y + visibleSize.height - 252 - txtName->getContentSize().height/2 ));
    txtName->setColor(Color3B(54, 72, 99));
    txtName->setPlaceHolderColor(Color4B(54, 72, 99, 172));
    txtName->addEventListener(CC_CALLBACK_2(ServerListScene::txtNameEvent, this));
    this->addChild(txtName);
    
    // load the name
    UserDefault * def = UserDefault::getInstance();
    std::string name = def->getStringForKey("player_name", "");
    txtName->setString(name);

    
    // menu
    menu = Menu::create(btnExit, btnAbout, btnHelp, logo, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
    
    // Server names menu
    menuView = ui::ListView::create();
    menuView->setDirection( ui::ScrollView::Direction::VERTICAL );
    menuView->setClippingEnabled(false);
    menuView->setPosition(Vec2(origin.x, origin.y + visibleSize.height/2));
    menuView->setBounceEnabled(true);
    
    //menuView->pushBackCustomItem(lblSearching);
    
    this->addChild(menuView);
    
    
    
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
    auto findServersAction = RepeatForever::create(sequence);
    this->runAction(findServersAction);
}



void ServerListScene::startReceiveBlocks()
{
    auto callback = CallFunc::create(CC_CALLBACK_0(ServerListScene::receiveAllBlocks, this));
    auto delay = DelayTime::create(RECEIVE_TIMEOUT);
    auto sequence = Sequence::create(callback, delay, nullptr);
    auto receivePacketAction = RepeatForever::create(sequence);
    this->runAction(receivePacketAction);
}



void ServerListScene::receiveAllBlocks()
{
    Connector * c = Connector::getInstance();
    Blok * blok;
    
    // c->receive() returns 0, if no received packet is in the queue
    while( (blok = c->receive()) != nullptr )
    {
        switch ( blok->getType() )
        {
            case P_SERVER_NAME:
            {
                refreshServer(blok);
                break;
            }
                
            case P_CONNECTED:
            {
                onConnected(blok);
                break;
            }
                
            case P_CONNECTION_FAILED:
            {
                connectionFailed(blok);
                break;
            }
            
            default:
            {
                // packet ignored
                CCLOG("Packet %d ignored.", blok->getType());
                break;
            }
        }
        
        blok->deallocate();
    }
}



void ServerListScene::refreshServer(Blok * blok)
{
    // parse Blok
    auto name = __String::create( ServerNameBlok::ServerName(blok) );
    CCLOG("Server response: %s", name->getCString() );
    
    addOrUpdateServer(name, blok->getAddress());
}



void ServerListScene::addOrUpdateServer(cocos2d::__String * serverName, RakNet::SystemAddress address)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    int hash = (int) RakNet::SystemAddress::ToInteger( address );
    
    if( serverMap.count( hash ) == 0 )
    {
        // create new entry
        ServerMapEntry * s = new ServerMapEntry();
        s->inactiveSeconds = 0;
        s->address = new RakNet::SystemAddress(address); // copy adress (packet will be deallocated)
        serverMap[hash] = s;

        CCLOG("%s added (hash: %d).", serverName->getCString(), hash);
        std::string name(serverName->getCString());
        
        // add to the menu (img, background, label)
        auto btn = ui::Button::create("servername_bg.png", "servername_bg.png");
        btn->setAnchorPoint(Vec2(0, 0.5));
        btn->setPosition(Vec2( origin.x + visibleSize.width/2 - 525, origin.y + visibleSize.height - 452 ));
        btn->setContentSize(cocos2d::Size( 800, btn->getContentSize().height ));
        btn->setScale9Enabled(true);
        btn->setTitleText(name);
        btn->setTitleFontName("Monda-Bold.ttf");
        btn->setTitleFontSize(50);
        btn->setTitleColor(Color3B(54, 72, 99));
        auto lblSize = btn->getTitleRenderer()->getContentSize();
        btn->setContentSize(cocos2d::Size( 520, 10 + lblSize.height ));
        
        auto img = ui::Button::create("connect.png", "connect_clicked.png");
        img->setPosition(Vec2( origin.x + visibleSize.width/2 - 565, origin.y + visibleSize.height - 452 ));
        img->addClickEventListener(CC_CALLBACK_1(ServerListScene::btnServerClicked, this));
        img->setTag(hash);
        img->setUserData(btn); // set reference to the label
        
        this->addChild(btn);
        this->addChild(img);
        
        
        //menuView->setInnerContainerSize(cocos2d::Size(300, 500));
        //menuView->setContentSize(cocos2d::Size( menu->getContentSize().width, count * (menu->getContentSize().height) ));
        //menuView->ad
        
    } else
    {
        // server already exists - refresh server lifetime
        auto s = serverMap[hash];
        s->inactiveSeconds = 0;
    }
}



void ServerListScene::findServersStep()
{
    Connector::getInstance()->ping();
    decreaseServerLifetimes(); // refresh actually found servers
    CCLOG("[ServerListScene] Searching servers...");
}



void ServerListScene::decreaseServerLifetimes()
{
    for(std::map<int, ServerMapEntry*>::iterator i = serverMap.begin(); i != serverMap.end(); i++)
    {
        // iterator->first = key
        // iterator->second = value
        
        i->second->inactiveSeconds++;
        CCLOG("%s lifetime set to %d", i->second->address->ToString(), (int) i->second->inactiveSeconds);
        
        if( i->second->inactiveSeconds >= SERVER_MENU_LIFETIME)
        {
            //delete
            CCLOG("%s removed for inactivity.",i->second->address->ToString());
            
            // delete menu entry
            int hash = i->first;
            auto img = (ui::Button * ) this->getChildByTag(hash);
            if(img != nullptr)
            {
                auto lbl = (ui::Button *) img->getUserData();
                this->removeChild(lbl);
                this->removeChild(img);
            }
            
            delete i->second->address;
            serverMap.erase(i->first);
            
            
            /*auto menu = (Menu *) this->getChildByTag( (int) RakNet::SystemAddress::ToInteger( * (i->second->address) ));
            this->removeChild(menu);*/
            
            // if missing this, when only one server, app breaks (iterator is behind the end)
            if( serverMap.size() == 0 || i == serverMap.end() ){
                return;
            }
        }
        
    }
    
}



void ServerListScene::onConnected(Blok * blok)
{
    CCLOG("Connected to %s", blok->getAddress().ToString());
    auto scene = LobbyScene::createScene();
    Director::getInstance()->replaceScene(scene);
}



void ServerListScene::connectionFailed(Blok * blok)
{
    int hash = (int) RakNet::SystemAddress::ToInteger( blok->getAddress());
    auto btn = (ui::Button *) this->getChildByTag(hash);
    btn->stopAllActions();
    btn->loadTextures("connect.png", "connect_clicked.png");
    btn->setRotation(0);
    
    Device::vibrate(0.5);
}



void ServerListScene::txtNameEvent(Ref * sender, ui::TextField::EventType type)
{
    ui::TextField * txtField = dynamic_cast<ui::TextField *>( sender );
    
    switch (type)
    {
        case ui::TextField::EventType::ATTACH_WITH_IME:
        {
            break;
        }

        case ui::TextField::EventType::DETACH_WITH_IME:
        {
            break;
        }
        
        case ui::TextField::EventType::INSERT_TEXT:
        {
            // save the new name
            UserDefault * def = UserDefault::getInstance();
            std::string name = txtField->getString();
            def->setStringForKey("player_name", name);
            break;
        }

        case ui::TextField::EventType::DELETE_BACKWARD:
        {
            // save the new name
            UserDefault * def = UserDefault::getInstance();
            std::string name = txtField->getString();
            def->setStringForKey("player_name", name);
            break;
        }
    }
}



void ServerListScene::btnServerClicked(Ref * pSender)
{
    auto btn = (cocos2d::ui::Button *) pSender;
    int tag = btn->getTag(); // tag value is the key in serverMap
    btn->loadTextures("connecting.png", "connecting.png");
    btn->runAction( RepeatForever::create( RotateBy::create(1, 360) ) );
    
    if(tag == -1)
    {
        CCLOG("Tag not found. Can't connect.");
        return;
    }
    
    RakNet::SystemAddress address = *(serverMap[tag]->address);
    Connector::getInstance()->connect(address);
    CCLOG("[ServerListScene] Connecting to %s", address.ToString());
}



void ServerListScene::btnLeaveClicked(Ref * pSender)
{
    Connector::getInstance()->stop();
    Director::getInstance()->end();
    exit(0);
}