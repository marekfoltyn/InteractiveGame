#include "cocos2d.h"
#include "GameplayDefinitions.h"
#include "LobbyScene.h"

#include "Connector.h"
#include "ServerListScene.h"

#include "BoxFactory.h"

#include "Timer.cpp"

USING_NS_CC;
using namespace GameNet;

#define COLOR_GREEN Color4B(11, 112, 14, 255)
#define NODE_PAUSE "nodePause"
#define NODE_FORCE "nodeForce"


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
    auto callback = CallFunc::create(CC_CALLBACK_0(LobbyScene::receiveAllBoxes, this));
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
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
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
    
    // leave button
    auto disconnect = ui::Button::create();
    disconnect->setTitleText("leave");
    disconnect->setTitleFontName("Vanilla.ttf");
    disconnect->setTitleAlignment(TextHAlignment::CENTER);
    disconnect->setTitleColor(Color3B(51, 152, 54));
    disconnect->setTitleFontSize(100);
    disconnect->addTouchEventListener( CC_CALLBACK_2(LobbyScene::btnOnDisconnect, this) );
    disconnect->setAnchorPoint(Vec2(0, 1));
    int border = disconnect->getContentSize().height/4;
    disconnect->setPosition(Vec2( origin.x + border, origin.y + visibleSize.height - border ));
    this->addChild(disconnect);
    
    // leave button
    auto reset = ui::Button::create();
    reset->setTitleText("reset");
    reset->setTitleFontName("Vanilla.ttf");
    reset->setTitleAlignment(TextHAlignment::CENTER);
    reset->setTitleColor(Color3B(51, 152, 54));
    reset->setTitleFontSize(100);
    reset->addTouchEventListener(CC_CALLBACK_2(LobbyScene::pauseClick, this));
    reset->setAnchorPoint(Vec2(0, 0));
    border = reset->getContentSize().height/4;
    reset->setPosition(Vec2( origin.x + border, origin.y + border ));
    reset->setName(NODE_PAUSE);
    reset->setVisible(false);
    this->addChild(reset);
    
    // force-loading image
    auto force = Sprite::create("line.png");
    force->setName(NODE_FORCE);
    force->setScale(1,0);
    force->setAnchorPoint(Vec2(1, 0.5));
    force->setPosition(Vec2(origin.x + visibleSize.width - btnKick->getContentSize().width*1.05, origin.y + visibleSize.height/2));
    this->addChild(force);
}



void LobbyScene::receiveAllBoxes()
{
    Connector * c = Connector::getInstance();
    Box * box;
    
    // c->receive() returns 0, if no received packet is in the queue
    while( (box = c->receive()) != nullptr )
    {
        switch ( box->getType() )
        {
            case BOX_CONNECTION_LOST:
            {
                CCLOG("Connection lost.");
                onConnectionLost(box);
                break;
            }
              
            case BOX_COLLISION:
            {
#if ( CC_TARGET_PLATFORM != CC_PLATFORM_IOS ) // iOS ingores vibrate duration - too long vibrations
                Device::vibrate(0.05);
#endif
                CCLOG("Collision!");
                break;
            }
                
            case BOX_ADMIN:
            {
                auto pause = this->getChildByName(NODE_PAUSE);
                pause->setVisible(true);
            }
                
            default:
            {
                // packet ignored
                CCLOG("Packet %d ignored.", box->getType() );
                break;
            }
        }
        
        box->deallocate();
    }
}



void LobbyScene::btnOnDisconnect(Ref * sender, ui::Widget::TouchEventType type)
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
                []()
                {
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
            ),
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



void LobbyScene::onConnectionLost(Box * box)
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
            Util::Timer * timer = new Util::Timer(true);
            auto button = dynamic_cast<ui::Button*>(sender);
            button->setUserData(timer);
            
            auto force = dynamic_cast<Sprite*>( this->getChildByName(NODE_FORCE) );
            float scaleY = (0.8*visibleSize.height)/5.0;
            force->runAction(ScaleTo::create(Definitions::TIME_KICK_FORCE_MAX, force->getScaleX(), scaleY));
            
            BoxFactory::kickPressed()->send();
            
            break;
        }
        
        case ui::Widget::TouchEventType::CANCELED:
        case ui::Widget::TouchEventType::ENDED:
        {
            
            auto button = dynamic_cast<ui::Button*>(sender);
            auto timer = dynamic_cast<Util::Timer*>( (Util::Timer*)button->getUserData() );
            std::chrono::milliseconds elapsed = timer->Elapsed();
            unsigned long long int ms = elapsed.count();

            delete timer;
        
            auto forceSprite = dynamic_cast<Sprite*>( this->getChildByName(NODE_FORCE) );
            forceSprite->stopAllActions();
            forceSprite->setScaleY(0);
            
            if( ms >= Definitions::TIME_KICK_FORCE_MAX * 1000){
                ms = Definitions::TIME_KICK_FORCE_MAX * 1000;
            }
            
            unsigned int force = (ms / (Definitions::TIME_KICK_FORCE_MAX * 1000.0)) * 255.0;
            
            CCLOG("Elapsed %lld milliseconds, force %d%%, data = %d", ms, (int)(force/255.0 * 100.0), force);
            
            BoxFactory::kickReleased(force)->send(); // send to server
            Device::vibrate(0.1);
            
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
    Box * box = BoxFactory::acceleration(acc->x, acc->y, acc->z);
    box->send();
}

void LobbyScene::pauseClick(cocos2d::Ref *pSender, ui::Widget::TouchEventType type)
{
    
    auto button = dynamic_cast<cocos2d::ui::Button*>(pSender);
    int tag = 1;

    // wait
    if( type == ui::Widget::TouchEventType::ENDED ||
       type == ui::Widget::TouchEventType::CANCELED )
    {
        // disable text scaling
        button->getTitleRenderer()->setScale(1);
        
        
        // stop animation (click-trigger wont be called)
        button->stopActionByTag(tag);
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
                [button]()
                {
                    //TODO: pause game
                    CCLOG("Pause.");
                    button->removeAllChildren();
                    BoxFactory::resetScore()->send();
                }
            ),
            nullptr
        );
        action->setTag(tag);
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
