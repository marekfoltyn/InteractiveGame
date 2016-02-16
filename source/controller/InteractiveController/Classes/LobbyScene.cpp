#include "cocos2d.h"
#include "LobbyScene.h"

#include "Connector.h"
#include "ServerListScene.h"

#include "AccelerationBlok.h"
#include "CollisionBlok.h"
#include "KickBlok.h"
#include "TackleBlok.h"
#include "ResetScoreBlok.h"

USING_NS_CC;

#define COLOR_GREEN Color4B(11, 112, 14, 255)

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
    // cocos2d: 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    //auto rootNode = CSLoader::createNode("MainScene.csb");
    //addChild(rootNode);
         
    initGraphics();
    
    // start receiving bloks
    auto callback = CallFunc::create(CC_CALLBACK_0(LobbyScene::receiveAllBlocks, this));
    auto delay = DelayTime::create(RECEIVE_TIMEOUT);
    auto sequence = Sequence::create(callback, delay, nullptr);
    auto receivePacketAction = RepeatForever::create(sequence);
    this->runAction(receivePacketAction);

    // init accelerometer
    auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(LobbyScene::onAcceleration, this));
    Device::setAccelerometerEnabled(true);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}



void LobbyScene::initGraphics()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    // background color
    //auto background = cocos2d::LayerColor::create(COLOR_GREEN);
    auto background = Sprite::create("grass.png");
    background->setPosition(Vec2( origin.x + visibleSize.width/2, origin.y + visibleSize.height/2 ));
    this->addChild(background);
    
    // kick button
    auto btnKick = ui::Button::create("ball_big.png");
    btnKick->setAnchorPoint(Vec2(0.5, 0.5));
    btnKick->setPosition(Vec2(origin.x + visibleSize.width - btnKick->getContentSize().width/2, origin.y + visibleSize.height/2));
    btnKick->addTouchEventListener(CC_CALLBACK_2(LobbyScene::btnKickClick, this));
    this->addChild(btnKick);
    
    // kick label
    auto lblKick = Label::createWithTTF("Kick", "Vanilla.ttf", 250);
    lblKick->setTextColor(Color4B(124, 124, 124, 110));
    lblKick->setPosition( btnKick->getPosition() );
    this->addChild(lblKick);

    // tackle button
    auto btnTackle = ui::Button::create("ball_big.png");
    btnTackle->setAnchorPoint(Vec2(0.5, 0.5));
    btnTackle->setPosition(Vec2(origin.x + btnTackle->getContentSize().width*0.25, origin.y + visibleSize.height/2));
    btnTackle->setScale(0.5);
    btnTackle->addTouchEventListener(CC_CALLBACK_2(LobbyScene::btnTackleClick, this));
    this->addChild(btnTackle);

    // tackle label
    auto lblTackle = Label::createWithTTF("Pass", "Vanilla.ttf", 125);
    lblTackle->setTextColor(Color4B(124, 124, 124, 110));
    lblTackle->setPosition( btnTackle->getPosition() );
    this->addChild(lblTackle);
    
    // leave button
    auto disconnect = ui::Button::create();
    disconnect->setTitleText("leave");
    disconnect->setTitleFontName("Vanilla.ttf");
    disconnect->setTitleAlignment(TextHAlignment::CENTER);
    disconnect->setTitleColor(Color3B(51, 152, 54));
    disconnect->setTitleFontSize(100);
    disconnect->addTouchEventListener( CC_CALLBACK_2(LobbyScene::btnOnDisconnect, this) );
    disconnect->setAnchorPoint(Vec2(0, 1));
    disconnect->setPosition(Vec2( origin.x + visibleSize.width * 0.275, origin.y + visibleSize.height ));
    this->addChild(disconnect);
    
}



void LobbyScene::receiveAllBlocks()
{
    Connector * c = Connector::getInstance();
    Blok * blok;
    
    // c->receive() returns 0, if no received packet is in the queue
    while( (blok = c->receive()) != nullptr )
    {
        switch ( blok->getType() )
        {
            case P_CONNECTION_LOST:
            {
                CCLOG("Connection lost.");
                onConnectionLost(blok);
                break;
            }
              
            case P_COLLISION:
            {
#if ( CC_TARGET_PLATFORM != CC_PLATFORM_IOS ) // iOS ingores vibrate duration - too long vibrations
                Device::vibrate(0.05);
#endif
                CCLOG("Collision!");
                break;
            }
                
            case P_ADMIN:
            {
                setAsAdmin();
                break;
            }
                
            default:
            {
                // packet ignored
                CCLOG("Packet %d ignored.", blok->getType() );
                break;
            }
        }
        
        blok->deallocate();
    }
}



void LobbyScene::btnOnDisconnect(Ref * sender, ui::Widget::TouchEventType type)
{
    if( type != ui::Widget::TouchEventType::ENDED)
    {
        // we want only sucessfull click
        return;
    }
    
    auto c = Connector::getInstance();
    auto server = c->getServer();
    if( server != RakNet::UNASSIGNED_SYSTEM_ADDRESS )
    {
        c->disconnect(server);
    }
    CCLOG("User disconnected. Returning to main menu.");
    Scene * main = ServerListScene::createScene();
    Director::getInstance()->replaceScene( TransitionSlideInT::create(SCENE_TRANSITION, main) );
}



void LobbyScene::onConnectionLost(Blok * block)
{
    CCLOG("Connection lost. Returning to main menu.");
    Scene * main = ServerListScene::createScene();
    Director::getInstance()->replaceScene(main);
}



void LobbyScene::btnKickClick(Ref * sender, ui::Widget::TouchEventType type)
{
    switch (type)
    {
        case ui::Widget::TouchEventType::BEGAN:
        {
         
            KickBlok::create()->send(); // send to server
            Device::vibrate(0.1);
            break;
        }
        
        case ui::Widget::TouchEventType::CANCELED:
        case ui::Widget::TouchEventType::ENDED:
        {
            break;
        }
            
        default:
        {
            break;
        }
    }
}

void LobbyScene::btnTackleClick(Ref * sender, ui::Widget::TouchEventType type)
{
    switch (type)
    {
        case ui::Widget::TouchEventType::BEGAN:
        {
            
            TackleBlok::create()->send(); // send to server
            Device::vibrate(0.1);
            break;
        }
            
        case ui::Widget::TouchEventType::CANCELED:
        case ui::Widget::TouchEventType::ENDED:
        {
            break;
        }
            
        default:
        {
            break;
        }
    }
}

void LobbyScene::onAcceleration(cocos2d::Acceleration* acc, cocos2d::Event* unused_event)
{
    Blok * blok = AccelerationBlok::Create(acc);
    Connector::getInstance()->send(blok);
}

void LobbyScene::setAsAdmin()
{
    CCLOG("I am the admin!");
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
    
    // leave button
    auto reset = ui::Button::create();
    reset->setTitleText("reset");
    reset->setTitleFontName("Vanilla.ttf");
    reset->setTitleAlignment(TextHAlignment::CENTER);
    reset->setTitleColor(Color3B(51, 152, 54));
    reset->setTitleFontSize(100);
    reset->addTouchEventListener( [&] (cocos2d::Ref *pSender, ui::Widget::TouchEventType type) // definition of lambda function
    {
        if(type == ui::Widget::TouchEventType::ENDED){
            CCLOG("Reseting score...");
            ResetScoreBlok::create()->send();
        }
    });
    reset->setAnchorPoint(Vec2(0, 0));
    reset->setPosition(Vec2( origin.x + visibleSize.width * 0.275, origin.y ));
    this->addChild(reset);
}
