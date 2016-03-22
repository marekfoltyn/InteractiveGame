#ifndef __LOBBY_SCENE_H__
#define __LOBBY_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

#include "Connector.h"
#include "HandlerMap.h"
#include "Controller.h"

USING_NS_CC;
USING_NS_CC_EXT;

using namespace GameNet;

/**
 * The phone is connected to the server so the lobby scene is displayed.
 * This class represents the lobby, players can prepare for the game (they choose the color)
 * The lobby is represented by an empty game room - players can move freely, but they can't shoot etc.
 */
class ControlScene : public cocos2d::Layer
{
public:
    
    static const int SCENE_TAG = 1;
    static const char * NODE_PAUSE;
    
    /**
     * cocos2d: there's no 'id' in cpp, so we recommend returning the class instance pointer
     */
    static cocos2d::Scene * createScene();
    
    /**
     * Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
     */
    virtual bool init();

    /**
     * implement the "static create()" method manually
     */
    CREATE_FUNC(ControlScene);
    
    /**
     * load and set up cocos nodes and static graphics
     */
    void initGraphics();
        
    /**
     * send movement information to the server
     */
    void onAcceleration(cocos2d::Acceleration* acc, cocos2d::Event* unused_event);
    
    /**
     * user clicked on the disconnect button
     */
    void btnOnDisconnect(Ref * sender, ui::Widget::TouchEventType type);
    
    /**
     * kick button click
     */
    void btnKickClick(Ref * sender, ui::Widget::TouchEventType type);

    /**
     * tackle button click
     */
    void btnTackleClick(Ref * sender, ui::Widget::TouchEventType type);

    /**
     * set this controller as admin
     */
    void adminClick(cocos2d::Ref *pSender, ui::Widget::TouchEventType type);
    
private:
    
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    
    HandlerMap * handlerMap;
    Controller * controller;
    
};

#endif // __LOBBY_SCENE_H__
