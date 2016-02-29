#include "MainMenuScene.h"
#include "LobbyScene.h"

#include "Connector.h"
#include "ServerNameMessage.h"
#include "BoxFactory.h"

USING_NS_CC;

#define Z_INDEX_BG -100
#define Z_INDEX_BG_NAME -99
#define Z_INDEX_LOADING 100

#define FONT_SIZE_DEFAULT 70
#define FONT_OPACITY_HALF 100

#define NODE_SERVERS "menuView"
#define NODE_LOGO    "logo"
#define COLOR_GREEN Color4B(11, 112, 14, 255)
#define COLOR_BG_TRANSPARENT Color4B(255,255,255,24)

#define BORDER_DEFAULT 50

#define ACTION_RECEIVE_BOXES 100

Scene * MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}



bool MainMenuScene::init()
{
    // 1. super init first
    if( Layer::init() == false ){
        return false;
    }
    
    this->setTag(SCENE_TAG);
    
    initGraphics();
    
    startFindServers();
        
    return true;
}



void MainMenuScene::initGraphics()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    // background color
    auto background = Sprite::create("grass.png");
    background->setPosition(Vec2( origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 ));
    this->addChild(background, Z_INDEX_BG);
    
    // background game name
    auto phoneball = Label::createWithTTF("Phoneball", "Vanilla.ttf", 260);
    phoneball->setTextColor(COLOR_BG_TRANSPARENT);
    phoneball->setPosition(Vec2( origin.x + visibleSize.width/2, origin.y + visibleSize.height * 2.0/5 ));
    phoneball->setRotation(-10);
    //this->addChild(phoneball, Z_INDEX_BG_NAME);
    
    // game name
    auto gameName = Label::createWithTTF("P h o n e B a l l", "Vanilla.ttf", FONT_SIZE_DEFAULT);
    gameName->setPosition(Vec2( origin.x + visibleSize.width/2, origin.y + visibleSize.height - 1.3*BORDER_DEFAULT ));
    gameName->setColor(Color3B::WHITE);
    gameName->setOpacity(FONT_OPACITY_HALF);
    this->addChild(gameName);
    
    // ball logo
    auto logo = ui::ImageView::create("ball_medium_small.png");
    logo->setPosition(Vec2( origin.x + visibleSize.width/2, origin.y + visibleSize.height - 2*BORDER_DEFAULT - logo->getContentSize().height/2 ));
    logo->setName(NODE_LOGO);
    this->addChild(logo);
    
    // exit
    auto lblExit = Label::createWithTTF("Exit", "Vanilla.ttf", FONT_SIZE_DEFAULT);
    auto exit = MenuItemLabel::create(lblExit, CC_CALLBACK_1(MainMenuScene::btnLeaveClicked, this));
    exit->setAnchorPoint(Vec2(0.5,0));
    exit->setPosition( origin.x + visibleSize.width * 7.0/8, origin.y + BORDER_DEFAULT );
    auto menu = Menu::create(exit, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu);
    
    // stadiums label
    auto stadiums = Label::createWithTTF("Stadiums:", "Vanilla.ttf", FONT_SIZE_DEFAULT);
    //stadiums->setAnchorPoint(Vec2(0.5, 1));
    stadiums->setPosition(Vec2( origin.x + visibleSize.width * 1.0/4, origin.y + visibleSize.height - 2*BORDER_DEFAULT - logo->getContentSize().height/2 ));
    //stadiums->setOpacity(FONT_OPACITY_HALF);
    stadiums->setTextColor(COLOR_GREEN);
    this->addChild(stadiums);
    
    // player name label
    auto lblName = Label::createWithTTF("Player name:", "Vanilla.ttf", FONT_SIZE_DEFAULT);
    //lblName->setAnchorPoint(Vec2(0.5, 1));
    lblName->setPosition(Vec2( origin.x + visibleSize.width * 3.0/4, origin.y + visibleSize.height - 2*BORDER_DEFAULT - logo->getContentSize().height/2 ));
    //lblName->setOpacity(FONT_OPACITY_HALF);
    lblName->setTextColor(COLOR_GREEN);
    this->addChild(lblName);
    
    // logo background
    auto logo_bg = ui::ImageView::create("line.png");
    logo_bg->setPosition(Vec2( origin.x + visibleSize.width/2, origin.y + visibleSize.height - 2*BORDER_DEFAULT - logo->getContentSize().height/2 ));
    logo_bg->cocos2d::Node::setScale( (visibleSize.width - 2*BORDER_DEFAULT) / 100, 2*stadiums->getContentSize().height / 5);
    this->addChild(logo_bg, Z_INDEX_BG);
    
    // player name - text field
    auto txtName = ui::TextField::create("<your name>", "Vanilla.ttf", FONT_SIZE_DEFAULT);
    txtName->setMaxLength(12);
    txtName->setMaxLengthEnabled(true);
    txtName->setAnchorPoint(Vec2(0.5,1));
    txtName->setPosition(Vec2( origin.x + visibleSize.width * 3.0/4, lblName->getPosition().y - lblName->getContentSize().height - BORDER_DEFAULT));
    txtName->setColor(Color3B::WHITE);
    txtName->setPlaceHolderColor(Color4B(255, 255, 255, 124));
    txtName->addEventListener(CC_CALLBACK_2(MainMenuScene::txtNameEvent, this));
    this->addChild(txtName);
    
    // background behind text field
    auto bgName = ui::Button::create("name_bg.png");
    bgName->setScale9Enabled(true);
    bgName->setScaleY(0.1);
    bgName->setAnchorPoint(Vec2(0.5,0.5));
    bgName->setContentSize(cocos2d::Size( visibleSize.width * 1.0/2 - 4*BORDER_DEFAULT, 5  ));
    bgName->setPosition(Vec2( origin.x + visibleSize.width * 3.0/4, lblName->getPosition().y - 3*lblName->getContentSize().height - 2*bgName->getContentSize().height ));
    bgName->setOpacity(124);
    //this->addChild(bgName);

    
    // load the name
    UserDefault * def = UserDefault::getInstance();
    std::string name = def->getStringForKey("player_name", "");
    txtName->setString(name);

    
    // Server names menu
    auto menuView = ui::ScrollView::create();
    menuView->setName(NODE_SERVERS);
    menuView->setPosition(Vec2( origin.x + visibleSize.width * 1.0/4, lblName->getPosition().y - lblName->getContentSize().height - BORDER_DEFAULT ));
    menuView->setDirection( ui::ScrollView::Direction::VERTICAL );
    menuView->setContentSize(cocos2d::Size(visibleSize.width/2 - 2*BORDER_DEFAULT, menuView->getPosition().y - origin.y));
    menuView->setInnerContainerSize( menuView->getContentSize() );
    menuView->setAnchorPoint(Vec2( 0.5, 1));
    menuView->setBounceEnabled(true);
    menuView->setScrollBarEnabled(false);
    this->addChild(menuView);
    
}



void MainMenuScene::startFindServers()
{
    auto step = CallFunc::create(CC_CALLBACK_0(MainMenuScene::findServersStep, this));
    auto delay = DelayTime::create(FIND_SERVER_REPEAT_TIME);
    auto sequence = Sequence::create(step, delay, nullptr);
    auto findServersAction = RepeatForever::create(sequence);
    this->runAction(findServersAction);
    
    this->schedule([&](float dt)
    {
        //this->receiveBoxes();
    }, RECEIVE_TIMEOUT, CC_REPEAT_FOREVER, 0.0f, "pingServers");

}



void MainMenuScene::refreshServer(Box * box)
{
    // parse Box
    ServerNameMessage msg = ServerNameMessage();
    bool res = msg.deserialize( box->getData() );
    if( res == false){
        CCLOG("ServerNameMessage deserialization FAILED!");
        return;
    }
    
    auto name = msg.getServerName();
    
    CCLOG("Server response: %s", name.c_str() );
    
    addOrUpdateServer(name, box->getAddress());
    
}



void MainMenuScene::addOrUpdateServer(std::string serverName, RakNet::SystemAddress address)
{
    auto menuView = (ui::ScrollView *) this->getChildByName(NODE_SERVERS);
    auto origin = Director::getInstance()->getVisibleOrigin();
    int hash = (int) RakNet::SystemAddress::ToInteger( address );
    
    if( serverMap.count( hash ) != 1 || serverMap[hash] == nullptr ) // when deleted, set to nullptr (node is not deleted, bad memory acces during map loop)
    {
        // create new entry
        ServerMapEntry * s = new ServerMapEntry();
        s->position = serverCount;
        s->inactiveSeconds = 0;
        s->address = new RakNet::SystemAddress(address); // copy adress (packet will be deallocated)
        serverMap[hash] = s;

        CCLOG("%s added (hash: %d).", serverName.c_str(), hash);
        std::string name(serverName.c_str());
        
        // add to the menu (img, background, label)
        auto btn = ui::Button::create(/*"servername_bg.png", "servername_bg.png"*/);
        btn->setTag(hash);
        btn->setAnchorPoint(Vec2(0.5, 1));
        btn->setTitleText(name);
        btn->setTitleFontName("Vanilla.ttf");
        btn->setTitleFontSize(FONT_SIZE_DEFAULT);
        btn->setTitleColor(Color3B::WHITE);
        btn->addClickEventListener(CC_CALLBACK_1(MainMenuScene::btnServerClicked, this));
        btn->setPosition(Vec2(menuView->getInnerContainerSize().width/2,menuView->getInnerContainerSize().height - serverCount * 1.5 * btn->getContentSize().height ));
        
        menuView->setInnerContainerSize(cocos2d::Size( menuView->getInnerContainerSize().width, (serverCount+1) * 1.5 * btn->getContentSize().height ));
        menuView->addChild(btn);
        
        serverCount++;
        
        //repositionServers();
        
    } else
    {
        // server already exists - refresh server lifetime
        auto s = serverMap[hash];
        s->inactiveSeconds = 0;
    }
}



void MainMenuScene::findServersStep()
{
    Connector::getInstance()->ping();
    decreaseServersLifetime(); // refresh actually found servers
    CCLOG("[MainMenuScene] Searching servers...");
}



void MainMenuScene::decreaseServersLifetime()
{
    
    for(std::map<int, ServerMapEntry*>::iterator i = serverMap.begin(); i != serverMap.end(); i++)
    {
        // iterator->first = key
        // iterator->second = value
        if(i->second == nullptr)
        {
            continue;
        }
        
        i->second->inactiveSeconds++;
        CCLOG("%s lifetime set to %d", i->second->address->ToString(), (int) i->second->inactiveSeconds);
        
        if( i->second->inactiveSeconds >= SERVER_MENU_LIFETIME)
        {
            auto menuView = (ui::ScrollView *) this->getChildByName(NODE_SERVERS);
            
            //delete
            CCLOG("%s removed for inactivity.",i->second->address->ToString());
            
            // delete menu entry
            int hash = i->first;
            auto btn = (ui::Button * ) menuView->getChildByTag(hash);
            if(btn != nullptr)
            {
                cocos2d::Size lblSize = btn->getContentSize();
                menuView->removeChild(btn);
                
                // move other servers up
                for(std::map<int, ServerMapEntry*>::iterator j = serverMap.begin(); j != serverMap.end(); j++)
                {
                    if(j->second == nullptr) return;
                    
                    if(j->second->position > i->second->position)
                    {
                        auto entry = (ui::Button * ) menuView->getChildByTag( j->first );
                        entry->setPosition(Vec2( entry->getPosition().x, entry->getPosition().y + entry->getContentSize().height ));
                        j->second->position--;
                    }
                }
            }
            
            delete i->second->address;
            serverMap[i->first] = nullptr;
            serverCount--;
        }
        
    }
    
}



void MainMenuScene::connectionFailed(Box * box)
{
    auto logo = (ui::ImageView *) this->getChildByName(NODE_LOGO);
    logo->stopAllActions();
    //logo->setRotation(0);
    
    Device::vibrate(0.5);
}



void MainMenuScene::txtNameEvent(Ref * sender, ui::TextField::EventType type)
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



void MainMenuScene::btnServerClicked(Ref * pSender)
{
    auto btn = (cocos2d::ui::Button *) pSender;
    int tag = btn->getTag(); // tag value is the key in serverMap
    
    auto logo = (ui::ImageView *) this->getChildByName(NODE_LOGO);
    logo->runAction( RepeatForever::create( RotateBy::create(1, 360) ) );
    
    if(tag == -1)
    {
        CCLOG("Tag not found. Can't connect.");
        return;
    }
    
    RakNet::SystemAddress address = *(serverMap[tag]->address);
    Connector::getInstance()->connect(address);
    CCLOG("[MainMenuScene] Connecting to %s", address.ToString());
}



void MainMenuScene::btnLeaveClicked(Ref * pSender)
{
    Connector::getInstance()->stop();
    Director::getInstance()->end();
    exit(0);
}