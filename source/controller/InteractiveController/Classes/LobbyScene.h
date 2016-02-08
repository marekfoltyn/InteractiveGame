#ifndef __LOBBY_SCENE_H__
#define __LOBBY_SCENE_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

#include "Connector.h"

USING_NS_CC;
USING_NS_CC_EXT;

/**
 * The phone is connected to the server so the lobby scene is displayed.
 * This class represents the lobby, players can prepare for the game (they choose the color)
 * The lobby is represented by an empty game room - players can move freely, but they can't shoot etc.
 */
class LobbyScene : public cocos2d::Layer
{
public:
    
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
    CREATE_FUNC(LobbyScene);
    
    /**
     * load and set up cocos nodes and static graphics
     */
    void initGraphics();
    
    /**
     * receive Block processing loop
     * receives until RakNet returns 0 (empty packet queue)
     */
    void receiveAllBlocks();
    
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
     * connection was lost - (show the dialog? and) return to the server list scene
     */
    void onConnectionLost(Blok * block);
        
};

#endif // __LOBBY_SCENE_H__
