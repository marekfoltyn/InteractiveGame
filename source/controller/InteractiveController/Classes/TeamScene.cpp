#include "TeamScene.h"

#include "cocos2d.h"
#include "BoxFactory.h"
#include "GameplayDefinitions.h"
#include "Connector.h"
#include "Timer.cpp"

#include "MainMenuScene.h"

#include "AdminHandler.h"
#include "ConnectionLostHandler.h"
#include "TeamSelectHandler.h"
#include "DisconnectHandler.h"

#include "Player.h"

USING_NS_CC;
using namespace GameNet;

#define COLOR_GREEN Color4B(11, 112, 14, 255)
#define NODE_FORCE "nodeForce"

const char * TeamScene::NODE_PAUSE = "nodePause";

Scene * TeamScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setGravity(Vec2::ZERO);
    
    // 'layer' is an autorelease object
    auto layer = TeamScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}



// on "init" you need to initialize your instance
bool TeamScene::init()
{
    
    // cocos2d: 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    this->setTag(SCENE_TAG);
    
    director = Director::getInstance();
    connector = Connector::getInstance();
    
    //auto rootNode = CSLoader::createNode("MainScene.csb");
    //addChild(rootNode);
         
    initGraphics();
    
    // register handlers
    handlerMap = HandlerMap::create();
    controller = Controller::getInstance();
    
    // register handlers
    handlerMap->add(BOX_CONNECTION_LOST, new ConnectionLostHandler());
    handlerMap->add(BOX_ADMIN, new AdminHandler(nullptr));
    handlerMap->add(TOUCH_TEAM_SELECT, new TeamSelectHandler());
    handlerMap->add(VOID_DISCONNECT, new DisconnectHandler());
    
    // schedule box receiving
    this->schedule([&](float dt)
    {
        controller->receiveBoxes(handlerMap);
    },
    RECEIVE_TIMEOUT, CC_REPEAT_FOREVER, 0.0f, "receiveBoxes");

    
    return true;
}



void TeamScene::initGraphics()
{
    visibleSize = director->getVisibleSize();
    origin = director->getVisibleOrigin();
    
    // background color
    //auto background = cocos2d::LayerColor::create(COLOR_GREEN);
    auto background = Sprite::create("grass.png");
    background->setPosition(Vec2( origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 ));
    this->addChild(background);
    
    // leave button
    auto disconnect = ui::Button::create();
    disconnect->setTitleText("leave");
    disconnect->setTitleFontName("Vanilla.ttf");
    disconnect->setTitleAlignment(TextHAlignment::CENTER);
    disconnect->setTitleColor(Color3B(51, 152, 54));
    disconnect->setTitleFontSize(100);
    disconnect->addTouchEventListener( CC_CALLBACK_2(TeamScene::btnOnDisconnect, this) );
    disconnect->setAnchorPoint(Vec2(0, 1));
    int border = disconnect->getContentSize().height/4;
    disconnect->setPosition(Vec2( origin.x + border, origin.y + visibleSize.height - border ));
    this->addChild(disconnect);
    
    // header
    auto header = Label::createWithTTF("Select team","Vanilla.ttf", 100);
    header->setColor(Color3B::WHITE);
    header->setAnchorPoint(Vec2(1, 1));
    border = header->getContentSize().height/4;
    header->setPosition(Vec2( origin.x + visibleSize.width - border, origin.y + visibleSize.height - border ));
    this->addChild(header);

    // blue team
    auto blue = ui::Button::create("player_blue.png");
    blue->setTitleFontName("Vanilla.ttf");
    blue->setTitleAlignment(TextHAlignment::CENTER);
    blue->setTitleColor(Color3B::WHITE);
    blue->setTitleFontSize(20);
    blue->setPosition(Vec2(origin.x + (1.0/6)*visibleSize.width, origin.y + (visibleSize.height - border - disconnect->getContentSize().height)/2 ));
    blue->setScale(5);
    blue->setName(TEAM_BLUE);
    blue->addTouchEventListener( CC_CALLBACK_2(TeamScene::btnTeamSelected, this) );
    this->addChild(blue);
    
    auto bluePlayer = Player::create("blue_player");
    bluePlayer->setTeam(TEAM_BLUE);
    bluePlayer->getSprite()->setPosition(Vec2(origin.x + (1.0/6)*visibleSize.width, origin.y + (visibleSize.height - border - disconnect->getContentSize().height)/2 ));
    bluePlayer->getSprite()->setScale(5);
    bluePlayer->getSprite()->getChildByName(LABEL_NAME)->setVisible(false);
    this->addChild(bluePlayer->getSprite());
    
    // auto assign
    auto autoAssign = ui::Button::create("player_no_color.png");
    autoAssign->setTitleText("auto");
    autoAssign->setTitleFontName("Vanilla.ttf");
    autoAssign->setTitleAlignment(TextHAlignment::CENTER);
    autoAssign->setTitleColor(Color3B::WHITE);
    autoAssign->setTitleFontSize(20);
    autoAssign->setPosition(Vec2(origin.x + (3.0/6)*visibleSize.width, origin.y + (visibleSize.height - border - disconnect->getContentSize().height)/2 ));
    autoAssign->setScale(5);
    autoAssign->setName(TEAM_AUTO);
    autoAssign->addTouchEventListener( CC_CALLBACK_2(TeamScene::btnTeamSelected, this) );
    this->addChild(autoAssign);
    
    // red team
    auto red = ui::Button::create("player_red.png");
    red->setTitleFontName("Vanilla.ttf");
    red->setTitleAlignment(TextHAlignment::CENTER);
    red->setTitleColor(Color3B::WHITE);
    red->setTitleFontSize(20);
    red->setPosition(Vec2(origin.x + (5.0/6)*visibleSize.width, origin.y + (visibleSize.height - border - disconnect->getContentSize().height)/2 ));
    red->setScale(5);
    red->setName(TEAM_RED);
    red->addTouchEventListener( CC_CALLBACK_2(TeamScene::btnTeamSelected, this) );
    this->addChild(red);

    auto redPlayer = Player::create("red_player");
    redPlayer->setTeam(TEAM_RED);
    redPlayer->getSprite()->setPosition(Vec2(origin.x + (5.0/6)*visibleSize.width, origin.y + (visibleSize.height - border - disconnect->getContentSize().height)/2 ));
    redPlayer->getSprite()->setScale(5);
    redPlayer->getSprite()->getChildByName(LABEL_NAME)->setVisible(false);
    this->addChild(redPlayer->getSprite());

    
}



void TeamScene::btnOnDisconnect(Ref * sender, ui::Widget::TouchEventType type)
{
    auto button = dynamic_cast<cocos2d::ui::Button*>(sender);
    
    // wait
    if( type == ui::Widget::TouchEventType::ENDED ||
       type == ui::Widget::TouchEventType::CANCELED )
    {
        // disable text scaling
        button->getTitleRenderer()->setScale(1);
        
        
        // stop animation (click-trigger wont be called)
        button->stopActionByTag(Definitions::TAG_DELAY_CLICK);
        button->removeAllChildren();
        return;
    }
    
    if( type == ui::Widget::TouchEventType::BEGAN)
    {
        
#if ( CC_TARGET_PLATFORM != CC_PLATFORM_IOS ) // iOS ingores vibrate duration - too long vibrations
        Device::vibrate(0.05);
#endif
        // disable text scaling
        button->getTitleRenderer()->setScale(1);
        
        // run the click-delay (avoid accidental clicks)
        auto action = Sequence::create(
            DelayTime::create(Definitions::TIME_DELAY_CLICK),
            CallFunc::create(
                [&]()
                {
                    handlerMap->getVoidHandler(VOID_DISCONNECT)->execute();
                }),
               nullptr
               );
        action->setTag(Definitions::TAG_DELAY_CLICK);
        button->runAction(action);
        
        // add background "loading" animation
        auto bg = Sprite::create("line.png");
        int border = button->getContentSize().height/4;
        float scaleX = (2*border + button->getContentSize().width) / 100.0;
        float scaleY = (2*border + button->getContentSize().height) / 5.0;
        bg->setScale(0, scaleY);
        bg->setPosition(cocos2d::Vec2( button->getContentSize().width/2, button->getContentSize().height/2 ));
        button->addChild(bg,-1);
        auto loading = ScaleTo::create(Definitions::TIME_DELAY_CLICK, scaleX, scaleY);
        bg->runAction(loading);
    }
}



void TeamScene::btnTeamSelected(Ref * sender, ui::Widget::TouchEventType type)
{
    handlerMap->getTouchHandler(TOUCH_TEAM_SELECT)->execute(sender, type);
}
