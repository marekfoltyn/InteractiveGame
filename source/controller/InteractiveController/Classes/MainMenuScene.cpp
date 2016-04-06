#include "MainMenuScene.h"
#include "ControlScene.h"
#include "GameplayDefinitions.h"

#include "Connector.h"
#include "BoxFactory.h"

#include "ServersHandler.h"
#include "ConnectionResultHandler.h"
#include "ToggleVibrateHandler.h"
#include "AdminHandler.h"

USING_NS_CC;

#define Z_INDEX_BG -100
#define Z_INDEX_BG_NAME -99
#define Z_INDEX_LOADING 100

#define FONT_OPACITY_HALF 100

#define COLOR_BG_TRANSPARENT Color4B(255,255,255,24)

#define ACTION_RECEIVE_BOXES 100

const std::string MainMenuScene::NODE_SERVERS = "menuView";
const std::string MainMenuScene::NODE_LOGO    = "logo";
const std::string MainMenuScene::NODE_VIBRATE = "vibrate";

Scene * MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();
    layer->setTag(SCENE_TAG);

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}



MainMenuScene * MainMenuScene::getScene()
{
    return dynamic_cast<MainMenuScene*>( this->getChildByTag(SCENE_TAG) );
}



bool MainMenuScene::init()
{
    // 1. super init first
    if( Layer::init() == false ){
        return false;
    }
    
    this->setTag(SCENE_TAG);
    
    controller = Controller::getInstance();
    handlerMap = HandlerMap::create();
    
    // reset admin status
    controller->setAdmin(false);
    
    initGraphics();
    registerHandlers();
    scheduleBoxReceive();
    startFindServers();
    
    CCLOG("MainMenuScene initialized.");
    
    return true;
}



void MainMenuScene::registerHandlers()
{
    auto serverHandler = new ServersHandler(this);
    auto connectionHandler = new ConnectionResultHandler(this);
    
    // dynamic cast - ServersHandler implements two interfaces (both derived from BaseHandler),
    // so we have to decide, which interface will be casted to BaseHandler
    handlerMap->add(BOX_SERVER_NAME, dynamic_cast<BoxHandler*>(serverHandler));
    handlerMap->add(BOX_ADMIN, new AdminHandler(nullptr));
    handlerMap->add(BOX_CONNECTED, connectionHandler);
    handlerMap->add(BOX_CONNECTION_FAILED, connectionHandler);

    handlerMap->add(TOUCH_TOGGLE_VIBRATE, new ToggleVibrateHandler());
    handlerMap->add(VOID_PING_SERVERS, dynamic_cast<VoidHandler*>(serverHandler));
    handlerMap->add(CLICK_CONNECT_TO_SERVER, dynamic_cast<ClickHandler*>(serverHandler));
    
}



void MainMenuScene::scheduleBoxReceive()
{
    this->schedule([&](float dt)
    {
        controller->receiveBoxes(handlerMap);
    },
    RECEIVE_TIMEOUT, CC_REPEAT_FOREVER, 0.0f, "receiveBoxes");
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
    //exit->setAnchorPoint(Vec2(0.5,0));
    exit->setAnchorPoint(Vec2(1,0));
    //exit->setPosition( origin.x + visibleSize.width * 7.0/8, origin.y + BORDER_DEFAULT );
    exit->setPosition( origin.x + visibleSize.width - BORDER_DEFAULT, origin.y + BORDER_DEFAULT );
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
    txtName->setMaxLength(8);
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
    menuView->setPosition(Vec2( origin.x + visibleSize.width * 1.0/4, lblName->getPosition().y - lblName->getContentSize().height ));
    menuView->setDirection( ui::ScrollView::Direction::VERTICAL );
    menuView->setContentSize(cocos2d::Size(visibleSize.width/2 - 2*BORDER_DEFAULT, menuView->getPosition().y - origin.y));
    menuView->setInnerContainerSize( menuView->getContentSize() );
    menuView->setAnchorPoint(Vec2(0.5, 1));
    menuView->setBounceEnabled(true);
    menuView->setScrollBarEnabled(false);
    this->addChild(menuView);
    
    // vibrate button
    auto btnVibrate = ui::Button::create("vibrate.png");
    btnVibrate->setName(NODE_VIBRATE);
    btnVibrate->setAnchorPoint(Vec2(0, 0));
    btnVibrate->setPosition(Vec2(origin.x + BORDER_DEFAULT, origin.y + BORDER_DEFAULT));
    btnVibrate->addTouchEventListener([&](Ref * sender, ui::Widget::TouchEventType type){
        handlerMap->getTouchHandler(TOUCH_TOGGLE_VIBRATE)->execute(sender, type);
    });
    if( !controller->isVibrateEnabled() )
    {
        btnVibrate->setOpacity(Definitions::OPACITY_HALF);
    }
    // iOS does not use vibration settings
    #if ( CC_TARGET_PLATFORM == CC_PLATFORM_IOS )
    // show even on iOS if debug mode is enabled (I want to see it in iOS simulator)
    #ifndef DEBUG
        btnVibrate->setVisible(false);
    #endif
    #endif
    this->addChild(btnVibrate);
}



void MainMenuScene::startFindServers()
{
    this->schedule([&](float dt)
    {
        this->handlerMap->getVoidHandler(VOID_PING_SERVERS)->execute();
    },
    FIND_SERVER_REPEAT_TIME, CC_REPEAT_FOREVER, 0.0f, "pingServers");
}


void MainMenuScene::setLoadingAnimation(bool set)
{
    auto logo = (ui::ImageView *) this->getChildByName(NODE_LOGO);
    
    if(set)
    {
        logo->runAction( RepeatForever::create( RotateBy::create(1, 360) ) );
    }
    else
    {
        logo->stopAllActions();
    }
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
    this->handlerMap->getClickHandler(CLICK_CONNECT_TO_SERVER)->execute(pSender);
}



void MainMenuScene::btnLeaveClicked(Ref * pSender)
{
    Connector::getInstance()->stop();
    Director::getInstance()->end();
    exit(0);
}