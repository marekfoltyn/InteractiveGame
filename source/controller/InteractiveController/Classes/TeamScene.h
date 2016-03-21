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
class TeamScene : public cocos2d::Layer
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
    CREATE_FUNC(TeamScene);
    
    /**
     * load and set up cocos nodes and static graphics
     */
    void initGraphics();
    
    /**
     * disconnect button event
     */
    void btnOnDisconnect(Ref * sender, ui::Widget::TouchEventType type);
    
    /**
     * select team button event
     */
    void btnTeamSelected(Ref * sender, ui::Widget::TouchEventType type);
    
private:
    
    cocos2d::Director * director;
    GameNet::Connector * connector;
    
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    
    HandlerMap * handlerMap;
    Controller * controller;
    
};

#endif // __LOBBY_SCENE_H__
